# プロジェクト専用ライブラリディレクトリ (lib/)

このディレクトリは、プロジェクト固有の（プライベートな）ライブラリを配置するための場所です。

PlatformIO はこれらのライブラリを静的ライブラリとしてコンパイルし、実行ファイルにリンクします。

各ライブラリのソースコードは、以下のように個別のディレクトリに配置してください：

lib/ライブラリ名/[コード]

## ディレクトリ構造の例
Foo と Bar という2つのライブラリを作成する場合の構成例です。

```Plaintext
|--lib
|  |
|  |--Bar
|  |  |--docs（ドキュメント）
|  |  |--examples（サンプルコード）
|  |  |--src（ソースコード本体）
|  |     |- Bar.c
|  |     |- Bar.h
|  |  |- library.json（オプション：カスタムビルド設定など）
|  |
|  |--Foo
|  |  |- Foo.c
|  |  |- Foo.h
|  |
|  |- README --> このファイル
|
|- platformio.ini
|--src
   |- main.c
```
## src/main.c での使用例
Foo と Bar を使用する場合、以下のようにインクルードして呼び出します。

```C++
#include <Foo.h>
#include <Bar.h>

int main (void)
{
  // ライブラリの関数をここで実行
  ...
}
```

## ライブラリ依存関係ファインダー (LDF)
PlatformIO の Library Dependency Finder (LDF) は、プロジェクトのソースファイルをスキャンして、依存しているライブラリを自動的に検出します。

詳細については、以下の公式ドキュメント（英語）を参照してください。

- [PlatformIO LDF ガイド](https://docs.platformio.org/en/latest/librarymanager/ldf.html)