FROM debian:bookworm-slim
ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONUNBUFFERED=1

# Add Raspberry Pi repo so picamera2 and RPi.GPIO are available
RUN apt-get update -o Acquire::Check-Valid-Until=false \
        -o Acquire::AllowInsecureRepositories=true \
        -o Acquire::AllowDowngradeToInsecureRepositories=true && \
    apt-get install -y --no-install-recommends curl gnupg ca-certificates && \
    curl -fsSL https://archive.raspberrypi.com/debian/raspberrypi.gpg.key \
    | gpg --dearmor -o /usr/share/keyrings/raspberrypi.gpg && \
    echo "deb [signed-by=/usr/share/keyrings/raspberrypi.gpg] https://archive>
    > /etc/apt/sources.list.d/raspberrypi.list && \
    apt-get update && apt-get install -y \
        python3 \
        python3-pip \
        python3-flask \
        python3-rpi.gpio \
        libffi-dev \
        gcc \
        gfortran \
        libopenblas-dev \
        libavcodec59 \
        libavformat59 \
        libavutil57 \
        libswscale6 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*



RUN pip3 install --upgrade setuptools packaging --break-system-packages

RUN rm -rf \
    /usr/lib/python3/dist-packages/simplejpeg* \
    /usr/lib/python3/dist-packages/numpy* \
    /usr/lib/python3/dist-packages/cv2* \
    /usr/lib/python3/dist-packages/sklearn* \
    /usr/lib/python3/dist-packages/scipy*

# Install numpy 2.2.4 via pip — ignore the old apt version completely
RUN pip3 install "numpy==2.2.4" scikit-learn scipy joblib simplejpeg  \
    --break-system-packages \
    --only-binary=:all: \
    --index-url https://www.piwheels.org/simple/ \
    --extra-index-url https://pypi.org/simple/

RUN pip3 install opencv-python-headless \
    --break-system-packages \
    --only-binary=:all: \
    --index-url https://www.piwheels.org/simple/ \
    --extra-index-url https://pypi.org/simple/
RUN echo "/usr/lib/arm-linux-gnueabihf" > /etc/ld.so.conf.d/arm-libs.conf && >

WORKDIR /app
COPY requirements.txt .
RUN pip3 install -r requirements.txt --break-system-packages --no-build-isola>
COPY mergeall3.py .
COPY models/ ./models/

EXPOSE 5000
CMD ["python3", "mergeall3.py"]