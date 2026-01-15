# Build do jogo (binário em build/bin/)

# Build só o servidor (imagem final pequena - recomendado!)
docker build -t veredins-server:latest --target server .

# Rodar o servidor
docker run --rm -it -p 12345:12345/udp veredins-server:latest

# Build do jogo (se quiser testar em container)
docker build -t veredins-game:latest --target game-runtime .

# Rodar jogo (com display - exemplo básico, precisa X11 host)
docker run -it --rm \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  --gpus all \               # se tiver NVIDIA + nvidia-docker
  veredins-game:latest