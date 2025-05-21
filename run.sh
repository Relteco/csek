#!/bin/sh

echo ""
echo "=== CSEK Protocol Runner ==="
echo "1) Run demo"
echo "2) Run tests"
echo "3) Build only"
echo "4) Clean build"
echo "5) Run demo chat"
echo "0) Exit"
echo "============================"
printf "Select an option: "
read choice

case "$choice" in
  1)
    echo "[*] Building and running demo..."
    make
    ./bin/demo
    ;;
  2)
    echo "[*] Building and running tests..."
    make
    ./bin/test_csek
    ;;
  3)
    echo "[*] Building project only..."
    make
    ;;
  4)
    echo "[*] Cleaning build..."
    make clean
    ;;
  5)
    echo "[*] Building and running demo chat..."
    make bin/chat && ./bin/chat
    ;;
  0)
    echo "Exiting."
    ;;
  *)
    echo "Invalid option."
    ;;
esac