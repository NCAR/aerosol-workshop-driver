# aerosol-workshop-driver
Driver for use in an aerosol interface hack-a-thon

## Development

(high-level for now)

- Get the template code

For Fortran aerosol models:

```
cp template/fortran/* src/
```

For C++ aerosol models:

```
cp template/cpp/* src/
```

- Copy your aerosol model source code into `src/`

- Adapt the template code to wrap your model functions

- Build and run the executables

```
docker build -t aerosol-test .
docker run -it aerosol-test bash
cd build/
make test
```

- Copy the results out of the container
[WILL ADD]
