<h1 align="center">
  <br>
  <img src="etc/pr/logo.png" alt="Yokul Logo" title="Yokul Logo" width="200">
  <br>
</h1>

# Yokul

## An Embeddable Lisp

### Building

#### Windows

- Download the dependencies using `vcpkg`, and put the `.lib` and `.h` files in the right place in the `dep` folder.
  - `vcpkg.exe install gmp --triplet=x64-windows-static`
  - `vcpkg.exe install mpfr --triplet=x64-windows-static`
  - `vcpkg.exe install mpc --triplet=x64-windows-static`
  - `vcpkg.exe install icu --triplet=x64-windows-static`
- Install Visual Studio.
- Open Developer Command Prompt
- Run `build.bat`

### License

This project is license under GNU Lesser General Public License v3.0 only. ([SPDX:LGPL-3.0-only](https://spdx.org/licenses/LGPL-3.0-only.html))

See the [LICENSE](LICENSE) file for more details.

#### Attribution

This project uses the following components:

- GNU Multiple Precision Arithmetic Library
  - Homepage: https://gmplib.org/
  - License: [GNU Lesser General Public License v3.0 or later](https://www.gnu.org/licenses/lgpl-3.0.html)
  - SPDX Short identifier: [LGPL-3.0-or-later](https://spdx.org/licenses/LGPL-3.0-or-later.html)
- GNU MPFR
  - Homepage: https://www.mpfr.org/
  - License: [GNU Lesser General Public License v3.0 or later](https://www.gnu.org/licenses/lgpl-3.0.html)
  - SPDX Short identifier: [LGPL-3.0-or-later](https://spdx.org/licenses/LGPL-3.0-or-later.html)
- GNU MPC
  - Homepage: https://www.multiprecision.org/
  - License: [GNU Lesser General Public License v3.0 or later](https://www.gnu.org/licenses/lgpl-3.0.html)
  - SPDX Short identifier: [LGPL-3.0-or-later](https://spdx.org/licenses/LGPL-3.0-or-later.html)
- International Components for Unicode
  - Homepage: https://icu.unicode.org/
  - License: [UNICODE LICENSE V3](https://github.com/unicode-org/icu/blob/main/LICENSE)
  - SPDX Short identifier: [Unicode-3.0](https://spdx.org/licenses/Unicode-3.0.html)
