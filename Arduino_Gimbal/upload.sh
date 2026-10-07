#!/usr/bin/env bash
# Compile and upload the gimbal sketch to an Arduino Nano.
# Usage: ./upload.sh [port]   (default: first /dev/ttyUSB* or /dev/ttyACM*)
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
PORT="${1:-$(ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null | head -1)}"
[ -z "$PORT" ] && { echo "No Nano found. Plug it in and try again."; exit 1; }
echo "Using port $PORT"
# Most clone Nanos use the old bootloader; fall back to the new one if that fails.
arduino-cli compile --upload -p "$PORT" --libraries "$DIR/../libraries" --fqbn arduino:avr:nano:cpu=atmega328old "$DIR" ||
  arduino-cli compile --upload -p "$PORT" --libraries "$DIR/../libraries" --fqbn arduino:avr:nano "$DIR"
echo "Done. Serial monitor: arduino-cli monitor -p $PORT -c baudrate=115200"
