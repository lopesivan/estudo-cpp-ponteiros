# Dicas de projeto

## Copia o ultimo arquivo para **ex-x.cpp** para **ex-y.cpp**.
Onde `y = x + 1`.

`cp ex-01.cpp ex-02.cpp`

```bash
 ls -rtl *.cpp|
 cut -d" " -f9|
 tail -1      |
 sed 's/ex-\([0-9]\+\).cpp/\1/'|
 while read n; do printf "cp ex-%02d.cpp ex-%02d.cpp\n" "$n" "$((n+1))"; done|
 sh
```

## Deletar os executáveis

```bash
find . -not -iwholename '*.git*' -type f -executable -delete
```

