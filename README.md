# Pseudocode Interpreter

Interpreter sederhana untuk bahasa pseudocode. Dibuat sebagai proyek
pembelajaran untuk menambah pengalaman dan menjawab rasa penasaran.

## Fitur

- Assignment: `x <- 5`
- Aritmatika: `+ - * /` dengan precedence dan tanda kurung
- Perbandingan: `= < > <= >=`
- Literal boolean: `true`, `false`, `TRUE`, `FALSE`
- Input: `input(x)` atau `input(x, y, z)`
- Output: `output expr`
- Percabangan: `if ... then ... else ... endif`
- Perulangan `while ... do ... endwhile`
- Perulangan `for i <- 1 to N do ... endfor`
- Blok bersarang (nested if/while/for)

## Batasan

Fitur berikut **belum** didukung:

- Operator `AND` / `OR`
- Unary minus (`-5`)
- String literal (`"hello"`)
- Komentar
- Deklarasi `int x`
- Blok `Program ... endprogram`
- Modulo `%`
- `break` / `continue`
- Bilangan pecahan (hanya integer)

## Cara Build

### Windows

```bat
build.bat
```

### Linux / Mac

```sh
make
```

Binary hasil build akan ada di `bin/` (`bin/interpreter.exe` di Windows,
`bin/interpreter` di Linux/Mac).

## Cara Pakai

```sh
bin/interpreter example/faktorial.psdc
```

Untuk Windows:

```bat
bin\interpreter.exe example\faktorial.psdc
```

Contoh program (`example/faktorial.psdc`):

```text
input(n)
hasil <- 1
i <- 1
while i <= n do
    hasil <- hasil * i
    i <- i + 1
endwhile
output hasil
```

## Test

Test suite ada di folder `tests/`. Setiap file `cases/*.psdc` berisi
program yang menguji satu atau lebih fitur interpreter, dengan output
yang diharapkan di `cases/*.expected`. Kalau test butuh input, ada file
`cases/*.in`.

Jalankan semua test (setelah build):

```bat
cd tests
run_tests.bat
```

Di Linux/Mac:

```sh
cd tests
./run_tests.sh
```

Hasil saat ini: **23/23 pass**.

Cakupan test:

| Kategori | File |
|---|---|
| Assignment & aritmatika | `01_assignment`, `02_aritmatika`, `03_precedence` |
| Perbandingan | `04_perbandingan` |
| Percabangan | `05_if_basic`, `06_if_else`, `07_if_no_else`, `08_if_nested` |
| Perulangan while | `09_while`, `10_while_calc` |
| Perulangan for | `11_for`, `12_for_calc`, `13_for_nested`, `14_for_body_calc` |
| Literal boolean | `15_boolean_true`, `16_boolean_false` |
| Input | `17_input_single`, `18_input_multi` |
| Contoh program | `19_faktorial`, `20_fibonacci` |
| Error handling | `21_div_by_zero`, `22_undefined_var` |
| Gabungan | `23_kitchen_sink` |

## Struktur Kode

- `Lexer` — memecah source code menjadi token
- `Parser` — membangun AST dari token menggunakan recursive descent
- `Evaluator` — mengeksekusi AST dengan `unordered_map` sebagai environment

## Status

Proyek ini masih dalam tahap pengembangan. Semua fitur yang diklaim di
section **Fitur** sudah lolos test suite (23/23). Beberapa fitur tambahan
dan optimasi masih dalam daftar TODO.

## Known Issues / TODO

### Fitur yang belum ada

- [ ] Operator `AND` dan `OR` (token sudah ada di Lexer, tinggal ditangani di Parser dan Evaluator)
- [ ] Unary minus (`-5`, `-(a + b)`)
- [ ] String literal
- [ ] Komentar (`//` atau `#`)
- [ ] Modulo `%`
- [ ] Deklarasi `int x` dan blok `Program ... endprogram`
- [ ] `break` / `continue`

### Perbaikan internal

- [ ] `printTree` belum menelusuri `body`, `condition`, `alternative`, `arguments` (saat ini hanya traverse `left` dan `right`)
- [ ] Input tidak memvalidasi `std::cin` — kalau user input non-angka, stream jadi error state dan bisa bikin loop
- [ ] Memory leak pada `ASTNode` — node di-`new` tapi tidak pernah di-`delete`
- [ ] Belum ada CI (GitHub Actions) yang otomatis build + test di setiap push

### Optimasi performa

- [ ] Ganti `unordered_map<string, int>` dengan variable slot resolution (index-based) — estimasi 5–10× lebih cepat
- [ ] Simpan integer langsung di `ASTNode` saat parsing, jangan `stoi` tiap evaluasi
- [ ] Ganti chain `if` di `Evaluator.cpp` dengan `switch`
- [ ] Constant folding untuk ekspresi literal

## Lisensi

Proyek ini dilisensikan di bawah MIT License — lihat file [LICENSE](LICENSE).