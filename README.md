## Monster 全文檢索 ##

Monster 是 CBETA CBReader 所使用的全文檢索引擎。

## 編譯 ##

在主目錄下有個 makefile，unix 在主目錄下執行 make，會根據 makefile 在 output 目錄產生 Monster 的可執行檔。

## 設定檔 ##

請將 ini 目錄中的 Monster_default.ini 改名成 Monster.ini，並且放在與 Monster 主程式同一個目錄即可，
內容請依自己索引檔的位置修改。

## 執行方法 ##

Monster [字串] [起始數字] [列出筆數]

字串 :
  無字串 或為 ? 或為 help ： 列出本說明
  其他字串 : 當成是搜尋字串

起始數字 : 搜尋的起始 , 預設為 1
列出筆數 : 每次列出筆數, 預設為 10 , 最大值為 100
