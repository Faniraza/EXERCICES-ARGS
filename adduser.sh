#!/bin/bash

# ============================================
# Commande adduser personnalisée
# Usage: ./adduser.sh [options] <username>
# ============================================

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Fichiers de configuration
PASSWD_FILE="/etc/passwd"
SHADOW_FILE="/etc/shadow"
GROUP_FILE="/etc/group"
HOME_BASE="/home"

# ---- Vérification des droits root ----
if [ "$(id -u)" -ne 0 ]; then
    echo -e "${RED}Erreur : Ce script doit être exécuté en tant que root.${NC}"
    exit 1
fi

# ---- Fonction d'aide ----
usage() {
    echo "Usage: $0 [options] <username>"
    echo ""
    echo "Options:"
    echo "  -d <répertoire>   Répertoire home (défaut: /home/username)"
    echo "  -s <shell>        Shell de l'utilisateur (défaut: /bin/bash)"
    echo "  -g <groupe>       Groupe principal"
    echo "  -c <commentaire>  Commentaire (GECOS)"
    echo "  -h                Afficher cette aide"
    exit 0
}

# ---- Valeurs par défaut ----
SHELL_DEFAULT="/bin/bash"
HOME_DIR=""
GROUP=""
COMMENT=""

# ---- Lecture des options ----
while getopts "d:s:g:c:h" opt; do
    case $opt in
        d) HOME_DIR="$OPTARG" ;;
        s) SHELL_DEFAULT="$OPTARG" ;;
        g) GROUP="$OPTARG" ;;
        c) COMMENT="$OPTARG" ;;
        h) usage ;;
        *) usage ;;
    esac
done

# Décaler les arguments après les options
shift $((OPTIND - 1))

# ---- Vérification du nom d'utilisateur ----
USERNAME="$1"

if [ -z "$USERNAME" ]; then
    echo -e "${RED}Erreur : Nom d'utilisateur manquant.${NC}"
    usage
fi

# Validation du nom (lettres, chiffres, underscore, tiret)
if ! echo "$USERNAME" | grep -qE '^[a-z_][a-z0-9_-]{0,31}$'; then
    echo -e "${RED}Erreur : Nom d'utilisateur invalide '$USERNAME'.${NC}"
    exit 1
fi

# ---- Vérifier si l'utilisateur existe déjà ----
if grep -q "^$USERNAME:" "$PASSWD_FILE"; then
    echo -e "${RED}Erreur : L'utilisateur '$USERNAME' existe déjà.${NC}"
    exit 1
fi

# ---- Générer un UID unique ----
LAST_UID=$(grep -v "^#" "$PASSWD_FILE" | awk -F: '$3 >= 1000 && $3 < 65534 {print $3}' | sort -n | tail -1)
NEW_UID=$(( ${LAST_UID:-999} + 1 ))

# ---- Définir le répertoire home ----
if [ -z "$HOME_DIR" ]; then
    HOME_DIR="$HOME_BASE/$USERNAME"
fi

# ---- Définir le groupe (GID) ----
if [ -z "$GROUP" ]; then
    GROUP="$USERNAME"
    NEW_GID=$NEW_UID
    # Créer le groupe si inexistant
    if ! grep -q "^$GROUP:" "$GROUP_FILE"; then
        echo "$GROUP:x:$NEW_GID:" >> "$GROUP_FILE"
        echo -e "${GREEN}Groupe '$GROUP' créé avec GID=$NEW_GID.${NC}"
    fi
else
    NEW_GID=$(grep "^$GROUP:" "$GROUP_FILE" | cut -d: -f3)
    if [ -z "$NEW_GID" ]; then
        echo -e "${RED}Erreur : Le groupe '$GROUP' n'existe pas.${NC}"
        exit 1
    fi
fi

# ---- Ajouter l'utilisateur dans /etc/passwd ----
echo "$USERNAME:x:$NEW_UID:$NEW_GID:$COMMENT:$HOME_DIR:$SHELL_DEFAULT" >> "$PASSWD_FILE"
echo -e "${GREEN}Utilisateur '$USERNAME' ajouté avec UID=$NEW_UID.${NC}"

# ---- Ajouter une entrée dans /etc/shadow ----
LOCKED_PASS="!"
DATE_EPOCH=$(( $(date +%s) / 86400 ))
echo "$USERNAME:$LOCKED_PASS:$DATE_EPOCH:0:99999:7:::" >> "$SHADOW_FILE"

# ---- Créer le répertoire home ----
if [ ! -d "$HOME_DIR" ]; then
    mkdir -p "$HOME_DIR"
    # Copier les fichiers de base (profil, bashrc...)
    cp -r /etc/skel/. "$HOME_DIR/" 2>/dev/null
    chown -R "$NEW_UID:$NEW_GID" "$HOME_DIR"
    chmod 750 "$HOME_DIR"
    echo -e "${GREEN}Répertoire home '$HOME_DIR' créé.${NC}"
fi

# ---- Définir le mot de passe ----
echo -e "${YELLOW}Définir le mot de passe pour '$USERNAME' :${NC}"
passwd "$USERNAME"

echo -e "${GREEN}✔ Utilisateur '$USERNAME' créé avec succès !${NC}"
