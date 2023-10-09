#####################################################
# Stage: build-cpp
#
# This stage builds your C++ conversion application
# using the Makefile.
#####################################################
FROM debian:bookworm AS build-cpp
RUN apt-get update && apt-get install -y make g++

# Create a working directory
WORKDIR /src

# Copy the C++ files, libraries, and headers to the
# build container to build the application
COPY ./sdk/Makefile ./sdk/convert.cpp ./
COPY ./sdk/lib ./lib
COPY ./sdk/include ./include

# Run the relevant Make commands to compile the 
# application
RUN make dir && \
    make all

#####################################################
# Stage: download-libreoffice6
#
# This stage downloads an older version of LibreOffice
# from the LibreOffice archives since you can't download
# LibreOffice 6.x from apt-get anymore. Run this as a
# separate stage so the download doesn't hold up other
# stages.
#####################################################
FROM debian:bookworm AS download-libreoffice6
RUN apt-get update && apt-get install -y curl

# Create a working directory
WORKDIR /libreoffice
# Download the older version of LibreOffice using curl
RUN curl -O https://downloadarchive.documentfoundation.org/libreoffice/old/6.4.7.2/deb/x86_64/LibreOffice_6.4.7.2_Linux_x86-64_deb.tar.gz
# Extract the downloaded files so the *.deb files can
# be copied to the release container
RUN tar -xf LibreOffice_6.4.7.2_Linux_x86-64_deb.tar.gz 

#####################################################
# Stage: release
#
# This stage will build the final Docker image that
# gets deployed. It's based on the Node.js image since
# your REST API is developed in Express and Node.js.
#####################################################
FROM node:18-bookworm as release

# Install dependencies for LibreOffice
RUN apt-get update && apt-get -y install default-jre libreoffice

# Copy the LibreOffice 6.x files downloaded in the previous
# stage and install them
WORKDIR /temp
COPY --from=download-libreoffice6 /libreoffice/LibreOffice_6.4.7.2_Linux_x86-64_deb/DEBS .
RUN dpkg -i *.deb
RUN rm -rf /temp

# Update your LD_LIBRARY_PATH with the location of the Foxit
# PDF SDK library files so your C++ program can find them
ENV LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/app/sdk/lib"

# Create a working directory for the Node.js REST API
WORKDIR /app

# Copy the C++ application compiled earlier into an `./sdk` folder
# along with the Foxit PDF SDK library files
COPY --from=build-cpp /src/bin/rel_gcc/convert ./sdk/convert
COPY ./sdk/lib ./sdk/lib

# Copy the Node.js package.json file and install the dependencies
COPY package.json .
RUN npm install

# Copy the server.js file containing the code for the REST API
COPY server.js .

# Expose the port of the REST API
EXPOSE 3000

# Tell Docker how to start the REST API
ENTRYPOINT [ "node", "server.js" ]