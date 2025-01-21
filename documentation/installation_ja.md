ダウンロードいただきありがとうございます! プラグインは昔ながらの手順でインストールできます。

# MacOS

## [1] 適切なフォルダにプラグインを置く
プラグインの置き場所として、以下のシステムフォルダをおすすめします。

* `/Library/Audio/Plug-Ins/VST3` (VSプラグイン)
* `/Library/Audio/Plug-Ins/Components` (AUプラグイン)

## [2] プラグインを使用可能にする（Catalina以降）
制作者がApple Developer Programに登録していないため、プラグインは認証されていません。そのためデフォルトではプラグインを起動しようとしてもmacOSがブロックしてしまいますが、次の手順で起動できるようになります。

1. **ターミナル.app**を起動。`/アプリケーション/ユーティリティ`にあります。
2. 下記のコマンドを入力またはコピペし、エンターキーを押す。システムフォルダ以外のフォルダに置いた場合はパスを書き換えてください。
3. プロンプトがMacのパスワードを求めた場合、入力してエンターキーを押す。**マークは表示されません*。

### [2-1] VSTプラグイン用コマンド
```
sudo xattr -rd com.apple.quarantine "/Library/Audio/Plug-Ins/VST3/lulu.vst3"
```

[2-2] AUプラグイン用コマンド
```
sudo xattr -rd com.apple.quarantine "/Library/Audio/Plug-Ins/Components/lulu.component"
```

## [3] 完了
これでホストからプラグインを起動できるようになります。必要に応じて、ホストからプラグインをスキャンしてください。


<div style="page-break-before:always"></div>

# Windows

## [1] 適切なフォルダにプラグインを置く
プラグインの置き場所として、以下のシステムフォルダをおすすめします。

* `C:/Program Files/Common Files/VST3`

## [2] 完了
これでホストからプラグインを起動できるようになります。必要に応じて、ホストからプラグインをスキャンしてください。