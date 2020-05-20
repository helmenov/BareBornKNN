# GNUPLOTの使い方
このページはフリーのグラフ表示ソフト`gnuplot`の使い方を大まかに説明したページです．
1. [`gnuplot`の起動と終了](#sec1)
2. [ディレクトリの移動・パスの閲覧](#sec2)
3. [グラフを表示する](#sec3)
4. [ファイルデータをプロットする](#sec4)
5. [データ間に直線を引く](#sec5)
6. [ファイルからコマンド実行](#sec6)
7. [参考ウェブサイト](#bib)

## <a name="#sec1">1. `gnuplot`の起動と終了</a>

`kterm`で
```
% gnuplot
```
と入力すると`gnuplot`が起動します．`&`はつけないで下さい．起動後の表示
```
gnuplot> 
```
が`gnuplot`のコマンドプロンプトです．`gnuplot`を終了させるには
```
gnuplot> quit （または exit）
```
と入力します．

## <a name="#sec2">2. ディレクトリの移動・パスの閲覧</a>

`gnuplot`のコマンドプロンプトで
```
gnuplot> pwd
```
と入力するとカレントディレクトリを表示します．ディレクトリの移動には`cd`コマンドを使いますが
```
gnuplot> cd '..' (または cd "..")
```
と移動する先のディレクトリを `'` か `"` で囲ってください．ちなみに`ls`コマンドは使えません．

## <a name="#sec3">3. グラフを表示する</a>

$y=\cos{(x)}$のグラフを表示するには，コマンドプロンプトで
```
gnuplot> plot cos(x)
```
と入力します．このとき
```
gnuplot> plot [0:pi] cos(x)
```
と入力すると，$x$の範囲が$0$から$\pi$までになります．
```
gnuplot> plot cos(x) with dot
```
と入力するとグラフを点で表示します．他にも `with lines`，`with impulse`，`with points`，`with boxes`などがあります． 2つのグラフを重ねて描く場合には
```
gnuplot> plot cos(x), sin(x)
```
と関数をコンマでつなぎます．

## <a name="#sec4">4. ファイルデータをプロットする</a>

`test.dat`というファイルに1次元の数値データが格納されている場合，コマンドプロンプトで
```
gnuplot> plot 'test.dat'
```
と入力すると`test.dat`の中に書き込まれた数値をグラフで描きます．

## <a name="#sec5">5. データ間に直線を引く</a>

プロットされたデータ間に直線を引く方法を紹介する．例としてデータの座標が書かれたファイル`data1.txt`を以下のように準備しよう．

```
1.0 1.0
1.2 1.2
1.5 1.5
1.7 1.7
2.0 2.0
2.2 2.2
2.5 2.5
```
このデータをプロットするには
```
gnuplot> plot 'data1.txt'
```
と入力すればよい．次に，
```
gnuplot>set arrow from 1.2 , 1.2 to 1.5 , 1.5 nohead
```
と入力してEnterキーを押してから
```
gnuplot>replot
```
と入力してみよう．すると点(1.2, 1.2)から(1.5, 1.5)に直線が引かれたと思う．さらに
```
gnuplot>set arrow from 1.7,1.7 to 2.0,2.0 nohead
```
と入力して
```
gnuplot>replot
```
とすると点(1.7, 1.7)から(2.0, 2.0)にも直線が引かれたと思う．`set arrow` とは矢印を引くためのコマンドで `from` から `to` まで矢印を引きなさいという意味．最後の `nohead` は矢印の先を描くな，という意味であり，`nohead`をつけないと直線が矢印になる．ちなみに描いた直線をグラフ上から消したい場合には
```
gnuplot>set noarrow
```
と入力してreplotしよう．

## <a name="#sec6">6. ファイルからコマンド実行</a>

複数のコマンドをいちいち入力するのではなく，ファイルに複数のコマンドを書き込んでおいて一挙に実行する方法を紹介する．例えば，[データ間に直線を引くの項目](#sec5)で紹介したコマンドを一挙に行ないたいときにはファイルを用意して次のように書く：

```
plot 'data1.txt'
set arrow from 1.2,1.2 to 1.5,1.5 nohead
set arrow from 1.7,1.7 to 2.0,2.0 nohead
replot
```

このファイルの名前が例えば`test.txt`であったとするとプロンプトで
```
gnuplot>load 'test.txt'
```
と入力するだけで，データをプロットし，線を2本引き，それを`replot`するという一連の操作を一挙に行なってくれる．これを使えば複雑なグラフも簡単に描ける（ハズ...）．

## <a name="#bib">参考ウェブサイト</a>

- [GNUPLOTの第一歩](http://lagendra.s.kanazawa-u.ac.jp/ogurisu/manuals/gnuplot-intro/index.html)：金沢大の小栗栖先生のページ．はじめてgnuplotを触る人にはうってつけ．
- [gnuplot tips](http://art.aees.kyushu-u.ac.jp/members/kawano/gnuplot/)：九大の河野先生のページ．
- [gnuplotの使い方](http://www.al.cs.kobe-u.ac.jp/~inamoto/unix-tools/useful/gnuplot/index.html#examples)：神戸大の稲元さんのページ．
- [GNUPLOT 3.5 マニュアル](http://wwwal.kuicr.kyoto-u.ac.jp/www/accelerator/a4/gnuplot/gnuplot.html)：gnuplotのマニュアルを日本語訳したもの．
