
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

5. Build the project using conan:

```
conan build . -of build
```

Set of build commands is bundled here for convenience.

```
python3 -m venv .venv && \
source .venv/bin/activate && \
pip3 install -r requirements.txt && \
conan profile detect --force && \
conan install . -of build --build=missing && \
conan build . -of build
```