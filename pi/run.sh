#!/bin/bash
sudo docker run --privileged --network host \
  -v /dev:/dev \
  -v /run/udev:/run/udev:ro \
  -v /usr:/usr:ro \
  -v /lib:/lib:ro \
  -v /home/pi/venv2:/home/pi/venv2:ro \
  -v /home/pi/bank_sys:/app \
  -e PYTHONPATH=/home/pi/venv2/lib/python3.13/site-packages \
  -e LIBCAMERA_IPA_MODULE_PATH=/usr/lib/arm-linux-gnueabihf/libcamera \
  -e SUPABASE_URL="https://dtrmjuyfclfelfrqxezh.supabase.co" \
  -e SUPABASE_KEY="sb_secret_U24nWBwYZ-gadHJIGj9kUQ_MDDEg_By" \
  --entrypoint /usr/bin/python3.13 \
  bank_sys /app/mergeall3.py