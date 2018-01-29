# BBC Genesis Key Utility


An offline BBC key utility built with nodejs and Electron. This utility does two things:

- Generate a valid BBC keypair
- Validate an existing BBC keypair

This tool is experimental and downloadable executables are not yet available.

## Status
- MacOS - Tested, Functional
- Windows - Untested
- Linux - Untested

## Dependencies
- Nodejs & npm

## Building Executables Yourself

Clone the repo

```bash
git clone https://github.com/betterchainio/genesis.git
```

Navigate to keys directory

```bash
cd genesis/tools/keys
```

Install dependencies
```bash
npm install
```

**Method one:** Launch project with Electron

```bash
npm install -g electron
electron .
```

**Method Two:** Compile the project Electron package Manager

```bash
npm install -g electron-packager
npm run compile
```

You'll now find a **build** directory in the project root, where you can find an executable for your system.

## Compile for all Platforms

### Building for All Platforms

**Will only compile for all platforms on a mac**

_If running on a mac, you'll need to install xquartz and wine, easiest is through homebrew_

```bash
npm run compile-all
```
