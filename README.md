
To Build:

1. Create python virtual environment:

```
python3 -m venv .venv
source .venv/bin/activate
```

2. Install python conan dependency:

```
pip3 install -r requirements.txt
```

3. Create your conan build profile:

```
conan profile detect --force
```

4. Build and install dependencies defined in conanfile.txt

```
conan install . -of build --build=missing
```

5. Build the project using CMake:

```
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

6. Test executable should now be in build/test

```
./test/test
```

Set of build commands is bundled here for convenience.

```
python3 -m venv .venv
source .venv/bin/activate
pip3 install -r requirements.txt
conan prfile detecit --force
conan install . -of build --build=missing
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```