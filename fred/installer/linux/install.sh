#!/bin/bash

if [ "$EUID" -ne 0 ]; then
    echo "Please run as root: sudo bash install.sh"
    exit 1
fi

FRED_BIN="/usr/local/bin/fred"
FRED_SRC="$(dirname "$0")/fred"
REAL_HOME=$(eval echo ~$SUDO_USER)

echo ""
echo "Fred Runtime Installer"
echo "======================"
echo ""

if [ -f "$FRED_BIN" ]; then
    echo "Existing Fred installation found."
    echo "Removing old version..."
    rm -f "$FRED_BIN"
    echo "Old version removed!"
    echo ""
fi

echo "Installing Fred..."
cp "$FRED_SRC" "$FRED_BIN"
chmod +x "$FRED_BIN"
echo "Fred installed to $FRED_BIN"
echo ""

echo "Registering .frd file association..."

mkdir -p $REAL_HOME/.local/share/applications
cat > $REAL_HOME/.local/share/applications/fred.desktop << EOF
[Desktop Entry]
Name=Fred Runtime
Exec=bash -c 'fred "%f"; read -p "Press enter to exit..."'
MimeType=application/x-fred
Terminal=true
Type=Application
EOF

mkdir -p $REAL_HOME/.local/share/mime/packages
cat > $REAL_HOME/.local/share/mime/packages/fred.xml << EOF
<?xml version="1.0" encoding="UTF-8"?>
<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
    <mime-type type="application/x-fred">
        <comment>Fred File</comment>
        <glob pattern="*.frd"/>
    </mime-type>
</mime-info>
EOF

xdg-mime install $REAL_HOME/.local/share/mime/packages/fred.xml 2>/dev/null
update-mime-database $REAL_HOME/.local/share/mime 2>/dev/null
update-desktop-database $REAL_HOME/.local/share/applications 2>/dev/null
xdg-mime default fred.desktop application/x-fred 2>/dev/null

echo "Done!"
echo ""
echo "Restart your terminal and type 'fred' to get started."
echo ""