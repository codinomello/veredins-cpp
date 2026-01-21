#!/usr/bin/env bash
set -e

# ===============================
# CONFIG
# ===============================
CLIENT_DIR="client"
SERVER_DIR="server"
COMPOSE_FILE="docker-compose.yml"

# ===============================
# HELP
# ===============================
help() {
  echo "Uso: ./dev.sh <comando>"
  echo
  echo "Comandos disponíveis:"
  echo "  client-build      -> build do client (CMake)"
  echo "  client-run        -> build + roda o client"
  echo "  client-clean      -> limpa build do client"
  echo
  echo "  server-build      -> build da imagem do server"
  echo "  server-run        -> roda server via docker-compose"
  echo "  server-logs       -> logs do server"
  echo "  server-stop       -> para containers"
  echo
  echo "  infra-up          -> sobe DB + Redis + Server"
  echo "  infra-down        -> derruba tudo"
  echo
  echo "  clean-all         -> limpa tudo (containers + builds)"
  echo
}

# ===============================
# CLIENT (C++)
# ===============================
client-build() {
  echo "🎮 Buildando client..."
  cd "$CLIENT_DIR"
  make build
  cd ..
}

client-run() {
  echo "🎮 Rodando client..."
  cd "$CLIENT_DIR"
  make run
  cd ..
}

client-clean() {
  echo "🧹 Limpando client..."
  cd "$CLIENT_DIR"
  make clean
  cd ..
}

# ===============================
# SERVER (Go + Docker)
# ===============================
server-build() {
  echo "🧠 Buildando server (Docker)..."
  docker build -t veredins-server "$SERVER_DIR"
}

server-run() {
  echo "🧠 Subindo server..."
  docker compose up -d server
}

server-logs() {
  docker compose logs -f server
}

server-stop() {
  docker compose down
}

# ===============================
# INFRA (DB + Redis + Server)
# ===============================
infra-up() {
  echo "🐳 Subindo infra completa..."
  docker compose -f "$COMPOSE_FILE" up -d --build
}

infra-down() {
  echo "🐳 Derrubando infra..."
  docker compose -f "$COMPOSE_FILE" down
}

# ===============================
# CLEAN TOTAL
# ===============================
clean-all() {
  echo "🧨 Limpando tudo..."
  docker compose down -v || true
  rm -rf "$CLIENT_DIR/build"
}

# ===============================
# DISPATCH
# ===============================
case "$1" in
  client-build) client-build ;;
  client-run)   client-run ;;
  client-clean) client-clean ;;

  server-build) server-build ;;
  server-run)   server-run ;;
  server-logs)  server-logs ;;
  server-stop)  server-stop ;;

  infra-up)     infra-up ;;
  infra-down)   infra-down ;;

  clean-all)    clean-all ;;
  *)            help ;;
esac