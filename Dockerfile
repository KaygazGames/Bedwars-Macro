# Temel imaj
FROM ubuntu:22.04

ENV IDF_PATH=/opt/esp-idf
ENV PATH="$IDF_PATH/tools:$PATH"

# Gerekli paketleri yükle
RUN apt-get update && apt-get install -y \
    git wget flex bison gperf python3 python3-pip python3-setuptools \
    ninja-build ccache libffi-dev libssl-dev dfu-util \
    && rm -rf /var/lib/apt/lists/*

# ESP-IDF kur
RUN git clone --branch v5.1 --recursive https://github.com/espressif/esp-idf.git $IDF_PATH
RUN $IDF_PATH/install.sh

WORKDIR /project

# Default build komutu
CMD ["idf.py", "build"]
