# Prepare target env
CONTAINER_DISPLAY="0"
CONTAINER_NAME="ADAS-DOCKER"
CONTAINER_HOSTNAME="schickling/opencv"

# Create a directory for the socket
mkdir -p display/socket
touch display/Xauthority

# Get the DISPLAY slot
DISPLAY_NUMBER=$(echo $DISPLAY | cut -d. -f1 | cut -d: -f2)

# Extract current authentication cookie
AUTH_COOKIE=$(xauth list | grep "^$(hostname)/unix:${DISPLAY_NUMBER} " | awk '{print $3}')

# Create the new X Authority file
xauth -f display/Xauthority add ${CONTAINER_HOSTNAME}/unix:${CONTAINER_DISPLAY} MIT-MAGIC-COOKIE-1 ${AUTH_COOKIE}

# Proxy with the :0 DISPLAY
socat TCP4:localhost:60${DISPLAY_NUMBER} UNIX-LISTEN:display/socket/X${CONTAINER_DISPLAY} &

# Launch the container
docker run -it --rm \
  -e DISPLAY=:0 \
  -v ${PWD}/display/socket:/tmp/.X11-unix \
  -v ${PWD}/display/Xauthority:/home/xterm/.Xauthority \
  --hostname ${CONTAINER_NAME} \
  ${CONTAINER_HOSTNAME}