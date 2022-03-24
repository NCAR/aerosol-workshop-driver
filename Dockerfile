from fedora:33

RUN dnf -y install \
    gcc-fortran \
    gcc-c++ \
    gcc \
    cmake \
    make \
    netcdf-fortran-devel \
    git \
    valgrind \
  && dnf clean all

COPY . /aerosol/

# build the aerosol demo code
RUN mkdir build \
    && cd build \
    && cmake ../aerosol \
    && make
