﻿// -*- mode:c++; coding:utf-8-ws -*-
#ifndef MY_CONFIG_H
#define MY_CONFIG_H

// clang-format off

/*
●やりたいこと.
- [ ] 2015.6.2
  検索文字列がある行番号の色を変更したい.

- [ ] 2015.6.5
  bug?, 単語を削除する際、一瞬選択状態になる

- [?] 2015.6.5
  bug, カーソル移動したときに移動前の状態が一瞬残る
  \view\CEditView_Scroll.cpp:void CEditView::ScrollDraw() があやしい?
  ScrollWindowEx() で行われる更新をなんとかすればいい?

- [ ] 2015.6.30
  コメント内の検索文字列はコメント色の影響を受ける.

- [ ] 2015.7.2
  開いているタブのファイル名をコピー.

- [ ] 2015.8.4
  タスクバーアイコンのちらつき
  \window\CTabWnd.cpp:CTabWnd::ShowHideWindow()
  SendMessageTimeout() と TabWnd_ActivateFrameWindow() の関係

- [ ] 2017.1.10
  bug?, 画面上端下端でキャレットが消えたタイミングでスクロールさせるとキャレットが消えたままスクロールする

- [ ] 2017.3.3
  テキスト描画、文字の右端が欠ける
  [patchunicode:#588]をあてて目立たなくはしている, 続けて描画されれば欠けない
  [patchunicode:#860]をあてれば解消しそう
    sakura_core\view\CEditView_Paint.cpp
    pcFigureManager->GetTextFigure().DrawImp(pInfo, nPosBgn, pInfo->GetPosInLogic() - nPosBgn);

- [ ] 2017.4.4
  BkSpを押したときにタブ入力文字だけしかない場合は逆TABにする

- [ ] 2017.4.24
  正規表現検索で「単語単位で探す」をチェックできるようにする (処理は先端終端に \b をつける)

- [ ] 2017.5.13
  せっかくいろいろなデフォルトタイプがあるのだから任意のタイプを追加できるようにしたい
*/

// ● フォント
//   https://support.microsoft.com/ja-jp/kb/74299
//   http://d.hatena.ne.jp/itoasuka/20100104/1262585983
//
// lf.lfHeight = DpiPointsToPixels(-10); // 高DPI対応（ポイント数から算出）

// 拡張用レジストリキー
#define MI_REGKEY _T("Software\\sakura-mimix")

//------------------------------------------------------------------
// バージョン情報ダイアログの変更 2017.3.15
//------------------------------------------------------------------
#define MI_MOD_VERDLG
  #define PR_VER      2,15,0,0
  #define PR_VER_STR "2.15"

//-------------------------------------------------------------------------
// デバッグ用
//-------------------------------------------------------------------------

// デバッグ出力 2015.3.24
//#define MI_OUTPUT_DEBUG_STRING


//-------------------------------------------------------------------------
// 編集
//-------------------------------------------------------------------------

//------------------------------------------------------------------
// スクロール
//------------------------------------------------------------------
#define MI_MOD_SCROLL
  // 水平スクロールの変更
  //  - スクロール開始マージンを 1 に変更。画面の端でスクロール開始 2014.5.7
  //  - スクロール幅を 16 に設定。一度に大きく移動することで見やすくする (Imitate 'Notepad') 2015.9.2
  #define MI_HORIZONTAL_SCR (16)
  // 垂直スクロールの変更
  //  - スクロールマージンを 0 に変更 2017.4.9
  #define MI_VERTICAL_SCR (0)

//------------------------------------------------------------------
// カーソルが大きく移動する処理ではカーソル行をセンタリングする 2017.4.13
//  (行番号ジャンプやタグジャンプ、アウトライン解析から移動した場合など)
//  - 同一画面内の移動はセンタリングしない
//    (REG/CenteringCursorJump:1)
//  ! CCaret::MoveCursor, 同期スクロールの対応がまだ
//  ? 'CURSOR_JUMP_AUTH' キーの有無で処理するか判断 (必要な場合は直前で作成)
//------------------------------------------------------------------
#define MI_MOD_CENTERING_CURSOR_JUMP

//------------------------------------------------------------------
// ミニマップ
//  - フォントサイズと表示幅を見やすい値に調整 (sakura.default.ini)
//  - クリックした位置が中央になるようにする 2017.5.15
//  - 表示エリア内ドラッグでもスクロールするようにする 2017.5.15
//  - 編集ウィンドウのスクロールでミニマップのスクロールバーのスクロールもする 2017.5.16
//  - 行TIPSを表示しない 2017.5.16
//  ! ミニマップのカラー設定OFFのときは枠を描画する
//  ! ミニマップに「行番号とテキストの隙間」はいらない
//  ! 検索文字列が見つかった行全体に色を付ける
//  ! ブックマーク行全体に色を付ける
//------------------------------------------------------------------
#define MI_MOD_MINIMAP
  #define MI_MINIMAP_NOLINETIP     (1)  // 行TIPSを表示しない
  #define MI_MINIMAP_BOOKMARK_DISP (1)  // ブックマーク行を全体表示する
  #define MI_MINIMAP_SEARCH_DISP   (2)  // 1:検索文字列を表示する, 2:検索文字列行を全体表示する
    // ミニマップ上の検索色
    // (REG/MiniMapSearchColor:0x00BBGGRR)
    #define MI_MINIMAP_SEARCH_COLOR (0x0000ffff)
  #define MI_MINIMAP_TYPE_SAKURA   (0)  // 
  #define MI_MINIMAP_TYPE_NPP      (1)  // Imitate 'Notepad++'
                                        //   スクロールバー非表示
                                        //   表示領域の端からスクロール開始
  #define MI_MINIMAP_TYPE_ST       (2)  // Imitate 'Sublime Text'
                                        //   スクロールバー非表示
                                        //   現在行に対応した位置に自動的にスクロール
  #define MI_MINIMAP_TYPE_DEFAULT MI_MINIMAP_TYPE_ST

//------------------------------------------------------------------
// タブ入力文字の切り替え(タブ<->空白)を追加
//  - S_ChangeTabWidthマクロ修正, 負の値を渡すとタブ文字の切り替え
//------------------------------------------------------------------
#define MI_MOD_CHANGE_TAB_WIDTH_MACRO


//-------------------------------------------------------------------------
// 表示
//-------------------------------------------------------------------------

//------------------------------------------------------------------
// UIフォント
//  - "ＭＳ Ｐゴシック" -> "MS Shell Dlg"
//  - .rcファイルは数が多いので置換対応
//------------------------------------------------------------------
#define MI_MOD_UI_FONT

//------------------------------------------------------------------
// 'BOM付' を 'BOM' に変更 2017.4.17
//  - わざわざ「付」をつけなくても認識できると判断とスペースの節約
//------------------------------------------------------------------
#define MI_MOD_WITH_BOM_TEXT

//------------------------------------------------------------------
// タブ名カラー
//------------------------------------------------------------------
#define MI_MOD_TAB_CAPTION_COLOR
  // 変更ドキュメントタブ名カラー
  // (REG/TabCaptionModifiedColor:0x00BBGGRR)
  #define MI_MODIFIED_TAB_CAPTION_COLOR (0x00d70000)
  // マクロ記録中ドキュメントタブ名カラー
  // (REG/TabCaptionRecMacroColor:0x00BBGGRR)
  #define MI_RECMACRO_TAB_CAPTION_COLOR (0x000000d8)

//------------------------------------------------------------------
// タブウィンドウ 2015.8.28
//  - ウィンドウまとめモードの切り替え時にスリープを10ms入れる(ちらつき抑制) 2017.4.6
//  - タブをダブルクリックで閉じる 2017.4.6 - 2017.4.7
//    (REG/DoubleClickClosesTab:1)
//  - ウィンドウが非アクティブなどきに非アクティブタブを選択したらそのタブをアクティブにする 2017.4.13
//  - WM_LBUTTONDOWN でウィンドウをアクティブにするようにする (修正前は WM_LBUTTONUP) 2017.4.14
//    この修正の影響で非アクティブウィンドウのドラッグができなくなった (対応予定)
//  - 境界線を描画しない, タブを詰める
//  - タブを閉じるボタンをグラフィカルにする
//  - 間に選択タブがあると右側のエッヂがないバグを修正 (となりのタブが上書き描画していた)
//  ? 各ウィンドウのタブウィンドウは生成時に自身の位置が選択されている状態から始まる
//    オーダーが変わらない限り選択タブが変わることはない
//    ウィンドウ切り替え時に自身が選択されたタブウィンドウが表示されることでタブを切り替えたように表現しているだけ
//    そのためスクロール状態からの切り替え時にスクロール位置が同期していない
//------------------------------------------------------------------
#define MI_FIX_TABWND

//------------------------------------------------------------------
// エディット画面 2017.4.28
//  - エディット画面のスタイルから WS_EX_STATICEDGE を外し境界線を描かないようにする
//    そのかわりにルーラー上部に COLOR_ACTIVEBORDER で境界線を描画する
//------------------------------------------------------------------
#define MI_FIX_EDITVIEW

//------------------------------------------------------------------
// ルーラー
//  - 行番号ラインは行番号の色で塗りつぶす 2017.4.11
//  ! 行番号ラインのクリックで全選択
//------------------------------------------------------------------
#define MI_MOD_RULER

//------------------------------------------------------------------
// 行を中央ぞろえにする 2014.3.26 - 2015.7.24
//  - デフォルトでは行は上揃えになっているので行間は下に付加される
//  x キャレットを行間含む高さにする
//------------------------------------------------------------------
#define MI_LINE_CENTERING

//------------------------------------------------------------------
// EOFのみの行にも行番号を表示 2017.3.10
//------------------------------------------------------------------
#define MI_MOD_EOFLN_DISP_NR

//------------------------------------------------------------------
// キャレット 2012.10.11
// 0: 変更なし
// 1-10: キャレットサイズ
// 11: カーソル位置の文字が 1バイトコードの時は 1px, 2バイトコードの時は 2px (Imitate 'Mozilla')
// 12: 半角入力の時は1px、全角入力の時は2px 2015.8.26
// (REG/CaretType:2)
//------------------------------------------------------------------
#define MI_MOD_CARET (2)

//------------------------------------------------------------------
// 半角空白文字
// - 半角空白文字を "・" で描画 (Imitate 'Sublime Text') 2013.6.2
// - Non-Breaking-Spaceを半角空白として表示する 2017.4.15
//------------------------------------------------------------------
#define MI_MOD_HAN_SPACE

//------------------------------------------------------------------
// タブ文字（矢印）の鏃(>)は表示しない (Imitate 'Sublime Text') 2015.5.25
//  - 「長い矢印」「短い矢印」→「線」 2016.8.19
//  -> タブ表示の文字指定廃止, 表示は線のみ 2017.3.29
//------------------------------------------------------------------
#define MI_MOD_TAB_MARK

//------------------------------------------------------------------
// カーソル行アンダーライン
//  - 左端から 2015.1.30
//------------------------------------------------------------------
#define MI_MOD_CUR_UL

//------------------------------------------------------------------
// 選択領域の色
//  - テキストと背景のブレンド率設定 2015.6.5
//  - 選択時のテキスト属性（太字、下線）に選択領域ではなく現在のテキストを使用する
//  - カラー設定は背景カラーのみ
//------------------------------------------------------------------
#define MI_MOD_SELAREA
  // 選択領域のブレンド率[%] 2015.6.5
  // (REG/SelectAreaTextBlendPer:0x00000000)
  // (REG/SelectAreaBackBlendPer:0x00000064)
  // (REG/SelectAreaBackBlendPer2:0x0000003C)
  #define MI_SELAREA_TEXT_BLEND_PER (0)
  #define MI_SELAREA_BACK_BLEND_PER (100)  // 選択範囲のブレンド率
  #define MI_SELAREA_BACK_BLEND_PER2 (60)  // 特定の下地のときの選択範囲のブレンド率

//------------------------------------------------------------------
// 空白,TAB,改行,EOFのカラー (Imitate 'Sublime Text') 2015.6.5
//  - 現在のテキスト色と現在の背景色をブレンドする (空白TABのカラー設定は無効化されます) 2015.6.8
//    対象は空白TABなどで、コントロールコードには適用されません
//  - 空白, タブ, 改行の色は他のカラー設定の影響を受けます
//------------------------------------------------------------------
#define MI_MOD_WS_COLOR
  // 空白,TAB,改行,EOF 現在のカラーのブレンド率[%] 2015.6.5
  // (REG/WhiteSpaceBlendPer:0x0000001E)
  #define MI_WS_BLEND_PER (30)
//						     
						     

//------------------------------------------------------------------
// カラー設定 2016.6.25
//  - カーソル位置縦線 テキストカラーのみ
//  - 折り返し記号 テキストカラーのみ
//------------------------------------------------------------------
#define MI_MOD_COLOR_STRATEGY

//------------------------------------------------------------------
// コメント行 2016.12.27
// 0x01: 改行以降もカラーを有効にする (Imitate 'Sublime Text')
//------------------------------------------------------------------
#define MI_MOD_COMMENT

//------------------------------------------------------------------
// 数値の色付け判定
//  - 正規表現で判定する 2017.4.21
//------------------------------------------------------------------
#define MI_MOD_NUMERIC_COLOR

//------------------------------------------------------------------
// ステータスバー 2015.6.10 - 2017.4.1
//  - ちらつき抑制
//  - カラムの並べ替え
//  - 左クリックでモード切り替えメニューを表示
//  - 左端カラムにパスを表示
//  - 「? 行 ? 桁」→「?:?」に変更
//  - タイプ名を表示 (左クリック: メニュー表示)
//  - タブサイズを表示 (左クリック: メニュー表示)
//  - 入力改行コードを主に使われているシステム名で表記
//------------------------------------------------------------------
#define MI_MOD_STATUSBAR

//-------------------------------------------------------------------------
// 機能
//-------------------------------------------------------------------------

//------------------------------------------------------------------
// プロファイルの読み書きにレジストリを使用可能にする
//  - レジストリキーがない場合はiniファイルから読み込む
//    (REG/NoReadProfilesFromRegistry:1) 1にするとレジストリから読み込まなくなります
//    (REG/NoWriteProfilesToRegistry:1) 1にするとレジストリに書き込まなくなります
//------------------------------------------------------------------
#define MI_USE_REGISTRY_FOR_PROFILES

//------------------------------------------------------------------
// プロファイル
//  - エントリが空文字の場合は書き込まない 2017.5.2
//  - 履歴は別ファイルで扱う (sakura.recent.ini) 2017.5.2
//  - カラー設定のインポートはカラー情報だけを適用させる 2017.5.4
//  - カラー設定の色に名前を付ける (fg,bg,white,blackなど) 2017.5.10
//  - sakura.default.iniを用意し、変更のない設定は書き込まないようにする 2017.5.11
//  - sakura.keywordset.jsonを用意し、強調キーワードの管理はこのファイルで行う 2017.5.13
//------------------------------------------------------------------
#define MI_MOD_PROFILES

//------------------------------------------------------------------
// メインメニューはデフォルトを使用する 2017.5.15
//  - 共通設定から「メインメニュー」タブを削除します
//------------------------------------------------------------------
#define MI_MOD_MAINMENU_FORCE_DEFAULT

//------------------------------------------------------------------
// 起動時に存在しないファイル・フォルダの履歴は削除する 2017.4.10
// (REG/DeleteHistoryNotExistAtStartup:1)
//------------------------------------------------------------------
#define MI_DELETE_HISTORY_NOT_EXIST_AT_STARTUP

//------------------------------------------------------------------
// 開かれているファイルを自己管理する前提で多重オープンの許可 2013.6.19
//  - Shiftを押しながらファイルドロップで多重オープン
//------------------------------------------------------------------
#define MI_MULTIPLE_OPEN_FILES

//------------------------------------------------------------------
// 最大数 2013.10.2, 2016.12.13
// \sakura_core\config\maxdata.h
// (REG/RecentSearchKeyMax:16)
// (REG/RecentReplaceKeyMax:16)
// (REG/RecentGrepFileMax:8)
// (REG/RecentGrepFolderMax:16)
//------------------------------------------------------------------
#define MI_MOD_MAXDATA
  #define MI_MAX_SEARCHKEY  (16) // 検索キー
  #define MI_MAX_REPLACEKEY (16) // 置換キー
  #define MI_MAX_GREPFILE   (8)  // Grepファイル
  #define MI_MAX_GREPFOLDER (16) // Grepフォルダ

//------------------------------------------------------------------
// 正規表現検索の際、検索文字列の正規表現記号をクォートする 2015.6.1
// PHPの preg_quote みたいなもの
// (REG/RegexpAutoQuote:1)
//------------------------------------------------------------------
#define MI_MOD_SEARCH_KEY_REGEXP_AUTO_QUOTE

//------------------------------------------------------------------
// 正規表現検索のときに「単語単位で探す」を使用できるようにする 2017.4.27
//  ! チェック時に検索文字列を \b で囲む
//------------------------------------------------------------------
//#define MI_MOD_ENABLE_WORD_SEARCH_REGEXP

//------------------------------------------------------------------
// 検索
//  ! 検索履歴からのオートコンプリート
//------------------------------------------------------------------
//#define MI_MOD_FIND

//------------------------------------------------------------------
// Grep 2015.8.24
//  - Grepするフォルダの指定を UI的に増やす (Imitate 'MIFES')
//    →カンマで区切るより分かれていた方が扱いやすいし、履歴管理もしやすい.
//  - 指定フォルダをすべてチェックをはずすと「現在編集中のファイルから検索」とする
//  - 「現在編集中のファイルから検索」をチェックした時の状態を保持しないようにする
//    →本来の「現在編集中のファイルから検索」を使用すると、
//      影響を受ける他のチェックボックスの状態が変更したまま戻らないのが嫌だから.
//  - ファイル(フィルタ)指定はフォルダのあとに置く (フォルダのほうが変更する機会が多いため)
//  - 検索中のダイアログを中央に置かない（リアルタイム時に見づらい）
//------------------------------------------------------------------
#define MI_MOD_GREP

//------------------------------------------------------------------
// 置換 2016.8.4
//  - 置換後文字列に置換前文字列を設定する
//    (REG/ReplaceTextToText:1)
//------------------------------------------------------------------
#define MI_MOD_REPLACE

//------------------------------------------------------------------
// フォルダ選択ダイアログ 2015.8.25
//  - CLSID_FileOpenDialogを使用する
//    使用するには Vista以降にする必要がある
//      -  WINVER=0x0500;_WIN32_WINNT=0x0500;_WIN32_IE=0x0501
//      -> WINVER=0x0601;_WIN32_WINNT=0x0601;_WIN32_IE=0x0800
// http://eternalwindows.jp/installer/originalinstall/originalinstall02.html
// https://msdn.microsoft.com/ja-jp/library/windows/desktop/ff485843(v=vs.85).aspx
// http://qiita.com/hkuno/items/7b8daa37d9b68e390d7e _WIN32_WINNT
// http://www.02.246.ne.jp/~torutk/cxx/vc/vcpp100.html
//------------------------------------------------------------------
#define MI_MOD_SELECTDIR

//------------------------------------------------------------------
// ダイアログを編集ウィンドウに配置 2017.4.4
//  - アウトライン解析
//  - 外部コマンド実行
//  - 検索
//  - 置換
//  - Grep
//  - Grep置換
//  - 指定行へジャンプ
//  - タグジャンプリスト
//  - ウィンドウ一覧表示
//  - 文字コードの指定
//  - 履歴とお気に入りの管理
//  - 更新通知及び確認
// 53         編集ウィンドウの表示位置、この場合は5分の3の位置に表示
// ||         指定できる値は1-9
// |+-- 分子
// +--- 分母
// (REG/PlaceDialogWindowTop:74)
// (REG/PlaceDialogWindowLeft:21)
//------------------------------------------------------------------
#define MI_MOD_DIALOG_POS
  #define MI_DIALOG_PLACE_TOP  (74)
  #define MI_DIALOG_PLACE_LEFT (21)

//------------------------------------------------------------------
// タグジャンプ一覧
//  - 表示するカラムの選別と並び替え 2015.8.27
//------------------------------------------------------------------
#define MI_MOD_TAGJUMP

//------------------------------------------------------------------
// タグファイル作成ダイアログ
//  - タグ作成フォルダの初期値を tags ファイルがあるところまで辿る 2017.5.12
//------------------------------------------------------------------
#define MI_MOD_TAGMAKEDLG

//------------------------------------------------------------------
// アウトライン解析ダイアログ 2016.12.14
//  - フォントをメインフォントにする
//  - ドッキング時、ウィンドウカラーにシステムカラーを使う
//    (REG/NoOutlineDockSystemColor:0)
//  - アウトライン解析ダイアログツリーのテーマに 'Explorer' を使用する 2017.5.1
//------------------------------------------------------------------
#define MI_MOD_OUTLINEDLG

//------------------------------------------------------------------
// ウェイトカーソル 2015.7.9
//  - 一部、正しい位置に修正
//  - 文字列削除時に表示しない（アンドゥのときなど）
//------------------------------------------------------------------
#define MI_MOD_WAITCUESOR


//-------------------------------------------------------------------------
// バグっぽいものを修正
//-------------------------------------------------------------------------

//------------------------------------------------------------------
// 検索ダイアログの「正規表現」が影響を受けないようにする
//  - 検索マーク切り替え時 2015.6.1
//  - インクリメンタルサーチ時 2016.12.14
//------------------------------------------------------------------
#define MI_FIX_SEARCH_KEEP_REGEXP

//------------------------------------------------------------------
// ミニマップをクリックしたときにフォーカスが移らないようにする 2017.5.15
//------------------------------------------------------------------
#define MI_FIX_MINIMAP_NOFOCUS

//------------------------------------------------------------------
// ルールファイル解析で「デフォルト」だとソートしていないため逆順になる 2017.5.9
//------------------------------------------------------------------
#define MI_FIX_FUNCLIST_RULEFILE

//------------------------------------------------------------------
// 行番号が非表示でブックマークが表示のときブックマークは線で描画する 2017.1.13
//------------------------------------------------------------------
#define MI_FIX_DRAW_BOOKMARK_LINE_NOGYOU

//------------------------------------------------------------------
// 行番号縦線を行番号の色で描画する 2016.12.21
//------------------------------------------------------------------
#define MI_FIX_LINE_TERM_TYPE

//------------------------------------------------------------------
// カーソル上下移動時に次の条件?のときに画面の更新が間に合わずに描画が崩れる 2015.8.4
//  - キーリピートが早い
//  - 裏で描画を頻繁に行うアプリが動いている
// →UpdateWindow() を呼び出すことで一時対応
//------------------------------------------------------------------
#define MI_FIX_CALL_CURSOR_MOVE_UPDATEWINDOW

//------------------------------------------------------------------
// カーソル移動時のちらつきを暫定で対処 2015.8.4
//  - スクロールした時に ScrollWindowEx() と再描画の同期がとれていない?
//  - MacTypeなどを使用すると描画の負荷が高くなり顕著になる。使わない場合は高速にやると再現する
// →MoveCursor()に処理をまとめてしばらく様子見 2015.8.5
// →修正を無効化して様子見 2017.4.8
//   →水平スクロール時にちらつくので最有効化 2017.4.9
//------------------------------------------------------------------
#define MI_FIX_CURSOR_MOVE_FLICKER


//
//#define USE_SSE2

#endif /* MY_CONFIG_H */
