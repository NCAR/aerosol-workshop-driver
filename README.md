# aerosol-workshop-driver
Driver for use in an aerosol interface hack-a-thon

## Development

(high-level for now)

### Get the template code

For Fortran aerosol models:

```
cp template/fortran/* src/
```

For C++ aerosol models:

```
cp template/cpp/* src/
```

### Adapt your aerosol code to the interface

- Copy your aerosol model source code into `src/`

- Adapt the template code to wrap your model functions
  - (FINISH WHEN READY)

### Build and run the executables in a Docker container

#### MacOS or Linux

From the `aerosol-workshop-driver/` folder, run:

```
docker build -t aerosol-test .
docker run -it --mount src="$(pwd)/output",target=/output,type=bind aerosol-test
cd build/
make test
```

#### Windows
From the `aerosol-workshop-driver/` folder, run:
**(UNTESTED)**

```
docker build -t aerosol-test .
docker run -it --mount src="c/Users/me/path/to/aerosol-workshop-driver/output",target=/output,type=bind aerosol-test
cd build/
make test
```

### Copy the results out of the container

Any files you put in `/output/` inside the container will be available in
`aerosol-workshop-driver/output/` outside the container.
