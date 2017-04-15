# サクラエディタ２改造版
\- 2.2.0.1をベースに[ココ](http://svn.code.sf.net/p/sakura-editor/code/sakura/trunk2)からマージ. ベースリビジョンからのマージ情報は[こちら](https://github.com/calette/sakura2201c/blob/master/changes_from_r4011.txt)  
\- 基本的に元ソースは残しつつの修正  
\- 他のテキストエディタでよかったところなどを移植  
\- バグ?とか気になったところの修正  
\- いくつかの[パッチ](https://sourceforge.net/p/sakura-editor/patchunicode/)をマージ  
\- プロポーショナルフォント関連はスルー (個人的に使用していないため)  
\- 挙動の制御にレジストリを使用しています (読み込み/書き込み)  

\- 動作環境  
`・Windows7以上 (Windows10 RS1,RS2で動作確認をしています)`  
\- ビルド環境  
`・MSVC2015を使用 (/O1 /MT _WIN32_WINNT=0x0601)`  
`・TCMallocを使用しています`  
`・Boostを使用しています. </extlib> へ </boost> をコピーしてください`  

<br>

<img src="https://raw.github.com/wiki/calette/sakura2201c/images/sakura0.gif" width="865px">
<img src="https://raw.github.com/wiki/calette/sakura2201c/images/sakura1.gif" width="695px">

<br>

## ■変更内容
いくつかの設定はレジストリで変更できます.<br>
`[HKEY_CURRENT_USER\SOFTWARE\sakura-calette]` を使用します.<br>
エントリが存在しない場合は作成してください.<br>

## ●ファイル系
\- 履歴 (検索、置換、Grep)の値を少なめに変更  
\- 起動時に存在しない履歴を削除する  
\- 多重オープンの許可  
`Shiftを押しながらファイルのドロップ`  

## ●操作,編集系
\- キャレットのサイズを変更可能に  
\- 水平スクロールの挙動を変更, メモ帳の挙動と同じにする  
\- カーソルが大きく移動する処理ではカーソル行をセンタリングする  
`行番号ジャンプやタグジャンプ、アウトライン解析から移動した場合など`  

\- タブ入力文字の切り替え機能 (タブ<->空白)  
`S_ChangeTabWidth マクロを修正, 負の値を設定すると相互に切り替えます`

## ●表示系
\- EOFのみの行 (起動時とか)にも行番号を表示  
\- 行を中央ぞろえにする  
\- デフォルトでは上揃えになっていて行の間隔が下に付加されている  
\- 半角空白文字を `･` で描画  
`Sublime Textみて、これだ！って思いました`  

\- タブ文字を線のみで描画  
`Sublime Textみて(ry`  

\- コメント行の背景カラーを改行以降も有効にする  
`行コメントとかブロックコメントの背景カラーを設定している場合にわかりやすくなります`  
`Sublime Tex(ry`  

\- 空白タブ、改行のカラーは現在のテキストカラーから自動で設定  
`コメント内の空白タブ、改行の色が色分けに影響を受けます`  
`Sub(ry`  

\- 選択範囲カラーのブレンド率を変更  
\- 太字装飾の文字列を選択したときに選択範囲カラーの装飾の影響を受けないように修正  
\- カーソル行アンダーラインを行番号から引っ張る  

## ●UI系
\- リソース (ダイアログ)のフォントを `9, "ＭＳ Ｐゴシック"` から `9, "MS Shell Dlg"` へ変更  
\- タブ名のカラーを変更  
\- タブをダブルクリックで閉じる  
\- ウィンドウ一覧ポップアップの表示位置のカスタマイズ  
\- 正規表現検索のときに正規表現記号をクォート  
`(`$10^` を検索する場合 `\$10\^` にする)`  

\- アウトライン解析ダイアログのフォントに設定フォントを使用  
`ドッキング時に背景カラーを使用しない (コントロール色のまま)`  

\- ステータスバーのカスタマイズ  
`ちらつき抑制、パスを表示、タブサイズ表示、タイプ名を表示`  
`改行コードに主に使われているシステム名を表記`  

\- Grepフォルダの指定を物理的に4つに増やした (`;` で区切ると履歴管理が面倒…)  
\- Grep「現在編集中のファイルから検索」をチェックした時の状態を保持しないようにする  
`現在編集中からのGrepって「今回だけ！」ってことが多いと思います`  

\- 置換ダイアログの置換後テキストに置換前テキストを設定  
\- ダイレクトジャンプ一覧の表示カラムを選別  

## ●バグっぽいのを修正
\- 検索マーク切り替え、インクリメンタルサーチの際に検索ダイアログの「正規表現」が影響を受けないように  
`常時、正規表現で検索しているとコレ結構ストレスたまります`  

\- カーソル移動時に描画が崩れる問題の仮対応  
`キーリピートの時間が速かったり、MacType使ってると負荷がかかってるみたいで描画が崩れたり行番号と本文の描画が同期してなかったりしてます.  
あんまりいい修正方法ではありませんが受けるストレスのほうが大事なので気にせず修正しました.  
この修正がこの改造版のすべてかと思います`  

## ●レジストリ詳細
[HKEY_CURRENT_USER\SOFTWARE\sakura-calette]<br>
存在しない場合は作成してください.<br>

\- CaretType (dword)
>    キャレットのサイズを  
        `0`: 変更なし  
        `1-10`: 指定サイズ (default:2)  
        `11`: 1バイトコードの時は1px、2バイトコードの時は2px  
        `12`: 半角入力の時は1px、全角入力の時は2px  

\- CenteringCursorJump (dword)
>    カーソル移動のセンタリングを  
        `0`: しない  
        `1`: する (default)  

\- DoubleClickClosesTab (dword)
>    タブをダブルクリックで  
        `0`: 閉じない  
        `1`: 閉じる (default)  

\- NoOutlineDockSystemColor (dword)
>    アウトライン解析ダイアログをドッキングしたときの背景カラーに  
        `0`: システムカラーを使う (default)  
        `1`: システムカラーを使わない  

\- PlaceDialogWindowLeft (dword)
>    ダイアログの横表示位置を変更  
    次の場合は編集ウィンドウの横半分(1/2)の位置に表示される  
        21 (default)  
        ||  
        |+-- 分子  
        +--- 分母  

\- PlaceDialogWindowTop (dword)
>    ダイアログの縦表示位置を変更  
    次の場合は編集ウィンドウの4/7の位置に表示される  
        74 (default)  
        ||  
        |+-- 分子  
        +--- 分母  

\- DeleteHistoryNotExistAtStartup (dword)
>    起動時に存在しない履歴を削除  
        `0`: 削除しない  
        `1`: 削除する (default)  

\- RecentSearchKeyMax (dword)
>    検索履歴数を変更  
        `16`: (default)  

\- RecentGrepFileMax (dword)
>    Grep履歴数を変更  
        `8`: (default)  

\- RecentGrepFolderMax (dword)
>    Grepフォルダ履歴数を変更  
        `16`: (default)  

\- RecentReplaceKeyMax (dword)
>    置換履歴数を変更  
        `16`: (default)  

\- RegexpAutoQuote (dword)
>    検索・置換時に「正規表現」を使用する場合、文字列を  
        `0`: クォートしない  
        `1`: クォートする (default)  

\- ReplaceTextToText (dword)
>    置換時に「置換前」テキストを「置換後」に  
        `0`: 設定しない  
        `1`: 設定する (default)  

\- SelectAreaBlendPer (dword)
>    選択範囲カラーのブレンド率を設定  
        `1-8bit`: 背景色ブレンド率 [0-100] (default:100)  
        `9-16bit`: テキスト色ブレンド率 [0-100] (default:0)  

\- WhiteSpaceBlendPer (dword)
>    空白タブのテキストとのブレンド率を設定  
        `1-8bit`: ブレンド率 [0-100] (default:30)  

\- TabCaptionModifiedColor (dword)
>    変更時のタブ名のテキストカラーを設定, 形式は 0x00BBGGRR  
        `0x00d70000`: (default)  

\- TabCaptionRecMacroColor (dword)
>    キーマクロ記録時のタブ名のテキストカラーを設定, 形式は 0x00BBGGRR  
        `0x000000d8`: (default)  

\- WinListPopupTop (dword)
>    ウィンドウ一覧ポップアップの表示位置を変更 (左上基準)  
        `0xffffffff`: センタリング (default)  

\- WinListPopupLeft (dword)
>    ウィンドウ一覧ポップアップの表示位置を変更 (左上基準)  
        `0xffffffff`: センタリング (default)  

\- WinListPopupWidth (dword)
>    ウィンドウ一覧ポップアップの表示幅を変更 (タブアイコン表示のときのみ有効)  
        `400`: (default)  
