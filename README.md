
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
 conan install . --output-folder=build --build=missing
```