# 手書き数字認識の演習

## 準備

Step 0: 準備として簡単な例題を解くことでプログラムの基本を復習しよう．以下の問題を番号順に解いて行こう．このとき一挙に全てを解こうとしないで，一つ一つ確実に解いていくことを心がけよう．

### Step 0-1:

- 自分の名前を `printf` 関数を使って表示せよ．
- 自分の名前をループを使って<img src="/tex/68399e6e2d2d99a90a9e8395f7dc1f11.svg?invert_in_darkmode&sanitize=true" align=middle width=24.657628049999992pt height=21.18721440000001pt/>回表示せよ．
- 上記の問題において，名前の前に何回目のループでの表示か分るようにループの回数を表示せよ．
- 上記の問題において，奇数番目のループの時だけ名前を表示するようにせよ．

### Step 0-2

- <img src="/tex/034d0a6be0424bffe9a6e7ac9236c0f5.svg?invert_in_darkmode&sanitize=true" align=middle width=8.219209349999991pt height=21.18721440000001pt/>から<img src="/tex/68399e6e2d2d99a90a9e8395f7dc1f11.svg?invert_in_darkmode&sanitize=true" align=middle width=24.657628049999992pt height=21.18721440000001pt/>までの総和を求めるプログラムを書け．
- 上で求めた総和を<img src="/tex/5dc642f297e291cfdde8982599601d7e.svg?invert_in_darkmode&sanitize=true" align=middle width=8.219209349999991pt height=21.18721440000001pt/>で割った値を小数点<img src="/tex/5dc642f297e291cfdde8982599601d7e.svg?invert_in_darkmode&sanitize=true" align=middle width=8.219209349999991pt height=21.18721440000001pt/>桁まで求めよ．

### Step 0-3

- 要素数が<img src="/tex/68399e6e2d2d99a90a9e8395f7dc1f11.svg?invert_in_darkmode&sanitize=true" align=middle width=24.657628049999992pt height=21.18721440000001pt/>の<img src="/tex/034d0a6be0424bffe9a6e7ac9236c0f5.svg?invert_in_darkmode&sanitize=true" align=middle width=8.219209349999991pt height=21.18721440000001pt/>次元配列を用意し，`i` 番目の要素に`1`から `i` までの総和を代入せよ．

10×10の2次元配列を用意し，その `( i , j )` 要素を
<p align="center"><img src="/tex/944a340401e2a19ce554f6919b22bb4c.svg?invert_in_darkmode&sanitize=true" align=middle width=71.90633009999999pt height=50.37231045pt/></p>
とせよ．

### Step 0-4

- 関数 `rand` を利用して乱数を10個生成せよ( [rand関数を使用したプログラム](/sample_codes/start1.c) )．
- 上記の問題で生成した乱数を大きい順に並べて表示するプログラムを作れ．

## 画像の入出力からkNN識別まで

### Step1: 

画像処理とプログラミングの復習：まずは![演習用画像](images/admix.pgm)をダウンロードし，画像閲覧ソフトで見てみよう．この画像を見ると，明るい画素と暗い画素が交互に混ざりあっているのがわかる．そこで暗い画素が上に，明るい画素が下になるように画素を並び替えた画像を作成してみよう（すなわち![このような画像](images/step1.png)を作成してください）．

演習用画像：![演習用画像](/images/admix.pgm)（画像サイズは128×128）

モノクロ画像についての解説ページ：[モノクロ画像の入出力](/step21/Readme.md)

サンプル画像：![Lenna.pgm](/images/Lenna.pgm)


### Step2: 

複数の画像を読み込むプログラムを作ることを考える．ここでは実際に数字パターンを100枚読み込んでみる．準備として以下のファイルをダウンロードして解凍しよう．

100枚の手書き数字の画像データ：[圧縮ファイル(tar,151KB)](/MNIST/test_image.tar)

ダウンロードしたら`kterm`で `tar -xvf test_image.tar` により解凍してください．

解凍したら複数の画像データをプログラムによって読み込み，各画像の画素値を配列に格納するプログラムを作成しよう（画像サイズは28×28）．

[画像ファイルを`sprintf`関数を使って順番に開くプログラムのサンプル](/sample_codes/C5.c)

100枚の画像ファイルを配列に展開するプログラム：[fileread_test.c](/sample_codes/fileread_test.c)

### Step3: 

Step2により100枚の手書き数字画像を開いて配列に格納することができたら，画像間のユークリッド距離を計算しよう．画像間のユークリッド距離は以下のようにして計算します．

画素数が<img src="/tex/f6c025352e9c1dc3d9e1b4ade55e74b2.svg?invert_in_darkmode&sanitize=true" align=middle width=74.86476194999999pt height=22.831056599999986pt/>の手書き数字画像データが全部で<img src="/tex/f9c4988898e7f532b9f826a75014ed3c.svg?invert_in_darkmode&sanitize=true" align=middle width=14.99998994999999pt height=22.465723500000017pt/>個あるとする．第<img src="/tex/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/>番目の画像データを1次元ベクトルで表現したものを <img src="/tex/d79b5a138dcf050e309ef533747a0a0d.svg?invert_in_darkmode&sanitize=true" align=middle width=243.35523465pt height=35.5436301pt/>と書く．このとき，画像の文字部分（黒）が1，背景部分（白）が0となるように画素値を変換しておく．さらに画素値の総和が1となるように <img src="/tex/649661e33dfa15621f40484c5176da74.svg?invert_in_darkmode&sanitize=true" align=middle width=97.09381604999999pt height=32.51169900000002pt/>と規格化する．画像<img src="/tex/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/>と<img src="/tex/36b5afebdba34564d884d347484ac0c7.svg?invert_in_darkmode&sanitize=true" align=middle width=7.710416999999989pt height=21.68300969999999pt/>とのユークリッド距離は

<p align="center"><img src="/tex/86dac7564e0705a1db69929d26bb768e.svg?invert_in_darkmode&sanitize=true" align=middle width=209.56429065pt height=59.17867724999999pt/></p>

により計算される．2つの画像（ベクトル）が似ているほど，この距離値は小さくなる．

（1枚目の画像とその他の画像の間の距離を計算して表示するプログラム：[dist_sample1.c](sample_codes/dist_sample1.c)）
　100枚の文字画像を用いて、画像間の距離値を計算できるようにする。

- 画像の黒が1、白が0となるように、画素値を変換する。
- 画素値の総和が1となるように規格化する。
- 画像間のユークリッド距離を計算する。
- 100枚の画像(No.1～No.100)を用いて、以下を表示してみる。

```
「No.1とNo.2 の距離」
「No.1とNo.3 の距離」
「No.1とNo.4 の距離」 ・・・
```

（画像間の距離と同時に画像のラベルを表示するプログラム：[dist_sample2.c](sample_codes/dist_sample2.c)）

100枚の文字画像に対するラベル（どの数字が書かれているかを示す情報）を読み込み、 プログラム中で利用できるようにする。

- 100枚の文字画像に対するラベルファイル(test_label.txt)をホームページのStep5の 部分からダウンロードしておく。
- プログラム中で、文字画像に加えてラベルファイルを読み込む。
- 上記２で作成したプログラムにおいて、対象とした画像が何という数字であるかを 距離と同時に表示するように改変する。

### Step4: 

未知の手書き数字データが与えられたときに，その数字が何の数字なのか識別することを考える． まず，パターン認識の基本を復習しよう．

[「わかりやすいパターン認識（第2版），石井ほか，オーム社（2019）」第1章](pattern_recognition_intro.pdf)

### Step5: 

識別法のうち，最近傍法（NN法）とk近傍法（k-NN法）について実際にプログラムを作成して，手書き数字を識別しよう．2000枚の学習データを用いて，まず100枚のテストデータを識別しよう．さらに1000枚のテストデータを識別して正答率を算出してみよう．

2000枚の学習データ（training data）：[圧縮ファイル(tar)](MNIST/train_image.tar) ・・・ラベル：[テキストファイル](MNIST/train_label.txt)

100枚のテストデータ（test data）：[圧縮ファイル(tar)](MNIST/test_image.tar) ・・・ラベル：[テキストファイル](MNIST/test_label.txt)

1000枚のテストデータ（test data）：[圧縮ファイル(tar)](MNIST/test_image1000.tar) ・・・ラベル：[テキストファイル](MNIST/test_label1000.txt)

［注意］大きな配列を静的に確保しようとすると，コンパイル時または実行時にエラーとなる場合がある．そのときは，`malloc` (または`calloc`)を用いてメモリを動的に確保するとよい．

2000枚の画像ファイルを`calloc`を使って確保した配列に展開するプログラム：[alloc_test.c](sample_codes/alloc_test.c)


（100枚のテストデータの１枚目と2000枚の学習データのそれぞれとの距離を計算して表示するプログラム：[dist_sample3.c](sample_codes/dist_sample3.c)）

100枚の文字画像（テストデータ）と同時に、2000枚の文字画像（学習データ）と ラベルファイルを読み込む。

2000枚の文字画像をプログラムに読み込む。このとき、配列のためのメモリを 動的に確保する。
2000枚の文字画像に対応するラベルファイル(train_label.txt)を読み込む。
テストデータの1枚目と2000枚の学習データとの距離値をそれぞれ計算して ラベルとともに表示する。

（100枚のテストデータの１枚目と2000枚の学習データのそれぞれとの距離を計算して小さい順に表示するプログラム：[dist_sample4.c](sample_codes/dist_sample4.c)）

100枚のテストデータの1枚目と、2000枚の学習データとの距離値をそれぞれ計算して、 小さい順に表示する。

距離値を計算して記憶しておく。
距離値の小さい順にソートする。ラベルデータも同時にソートされるように工夫する。
100枚のテスト画像のそれぞれについて、距離値が最も小さいものを識別結果とする（NN法）。 結果をもとに，正答率を算出する．

テストデータを1000枚に増やし，テスト画像のそれぞれについて、距離値が最も小さいものを識別結果とする。 結果をもとに，正答率を算出する．
アルゴリズムを下記のk近傍法（kNN法）に変更して実験をおこなう．kを変化させたときの 識別結果の違いを検討する．

### アルゴリズムk近傍法（k-Nearest-Neighbor rule, kNN）

1. テストデータを入力する．
2. テストデータとユークリッド距離が近い上位k個の学習データを求める．
3. k個の学習データのラベルを調べ，もっとも多いラベルをテストデータのラベルとして出力する．

このアルゴリズムでk=1とすれば最近傍法になり，それ以外のkを使えばk近傍法になる．

### 参考資料

実験で用いているデータにk近傍法を適用した場合のテストデータに対するエラー率と，学習データに対するエラー率を下のグラフに示す．横軸がk近傍法におけるk，縦軸がエラー率である．エラー率(%)とは（識別で正解したデータの個数）/（識別の対象となったデータの総数）を100倍したものである．赤がテストデータに対するエラー率，青が学習データに対するエラー率を示す．このエラー率の計算ではリジェクト（「わかりません」を出力することと同じ）は考慮されていない．

![](images/error.png)

時間があれば，このグラフを`gnuplot`で作成してみよう．

## 挑戦課題

### Step6:

今まで用いてきた数字データは数字の書かれている位置が決まっていた．そこで任意の位置にある数字を認識することを考えてみる．まず以下の[演習用画像2](images/step6.pgm)（画像サイズは80×80）をダウンロードしてみよ．そこに書かれている2つの数字を認識するにはどのようにすればよいか？方針が決まったらプログラミングで実際に認識処理を行ってみよう．

演習用画像：![演習用画像2](images/step6.pgm)

### Step7:

以下の[対象画像](images/contest.pgm)（画像サイズは133×84）から数字を探し出し，その数字が何であるのか出力するプログラムを作成してみよ．

![対象画像](images/contest.pgm)


![（右）対象画像，（左）正解](images/step7.png)

補助プログラム
[画像の拡大縮小と回転](sample_codes/rotation2.h)，[サンプルプログラム](sample_codes/sample.c)


