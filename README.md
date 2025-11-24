# Huffman Encoder - Mini Project Four

## 專案簡介

這是一個基於霍夫曼編碼（Huffman Coding）的字元編碼器專案。程式實作了 codebook 資料結構，用於儲存字元的編碼資訊，包括：
- 字元符號
- 出現次數
- 機率
- 位元編碼
- 自訊息量（Self-Information）

## 功能特色

✅ **Codebook 顯示**：顯示所有字元的編碼資訊表格  
🔧 **資料結構**：完整定義 codeword、codebook 和 Huffman tree 結構  
📊 **編碼資料**：包含 20 個字元的霍夫曼編碼範例

## 系統需求

- **作業系統**：Windows / Linux / macOS
- **編譯器**：GCC 或相容的 C 編譯器
  - Windows 推薦使用 MinGW-w64 (透過 MSYS2 安裝)
  - Linux/macOS 通常已預裝 GCC

## 安裝與編譯

### Windows (使用 MinGW-w64)

1. **安裝 MSYS2**：
   ```cmd
   winget install MSYS2.MSYS2
   ```

2. **安裝 GCC**：
   開啟 MSYS2 終端執行：
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```

3. **編譯程式**：
   ```cmd
   C:\msys64\mingw64\bin\gcc.exe encoder.c -o encoder.exe -O2 -Wall -Wextra
   ```

### Linux / macOS

```bash
gcc encoder.c -o encoder -O2 -Wall -Wextra
```

## 使用方式

### 執行程式

**Windows**：
```cmd
encoder.exe
```

**Linux / macOS**：
```bash
./encoder
```

### 預期輸出

程式會顯示 codebook 的內容表格：

```
========== Codebook Contents ==========
Symbol   Count    Probability  Bits       Self-Information  
-----------------------------------------------------------
?        1        0.021277     000000     5.554561          
<LF>     1        0.021277     000001     5.554561          
<CR>     1        0.021277     000010     5.554561          
a        1        0.021277     000011     5.554561          
...
========================================
```

## 專案結構

```
mini-project-four/
├── encoder.c          # 主程式原始碼
├── encoder.exe        # 編譯後的可執行檔 (Windows)
├── README.md          # 專案說明文件
├── .vscode/           # VS Code 配置
│   ├── tasks.json     # 建置任務配置
│   └── launch.json    # 除錯配置
└── .github/           # GitHub Actions CI/CD
    └── workflows/
        └── c_build.yml # 自動編譯流程
```

## 資料結構說明

### `codeword` 結構
```c
typedef struct _codeword {
    char symbol;              // 字元符號
    int count;                // 出現次數
    float probability;        // 機率
    char bits[32];            // 位元編碼字串
    float self_information;   // 自訊息量
} codeword;
```

### `codebook` 結構
```c
typedef struct _codebook {
    codeword words[256];      // 最多 256 個字元
    size_t size;              // 實際字元數量
} codebook;
```

### `huffman_node` & `huffman_tree` 結構
定義了霍夫曼樹的節點和樹結構（待實作）

## 開發計劃

### 已完成 ✅
- [x] 基本資料結構定義
- [x] Codebook 初始化
- [x] Codebook 顯示函數
- [x] GitHub Actions CI/CD 配置

### 待實作 🚧
- [ ] 霍夫曼樹建構演算法
- [ ] 編碼功能（文字 → 位元）
- [ ] 解碼功能（位元 → 文字）
- [ ] 從檔案讀取 codebook
- [ ] 計算壓縮統計資訊

## CI/CD

本專案使用 GitHub Actions 自動化建置和測試：
- 每次 push 程式碼時自動觸發
- 在 Ubuntu 環境中使用 GCC 編譯
- 自動執行程式驗證
- 上傳建置成品供下載

## 授權

本專案為學術用途。

## 作者

cychiang-ntpu

## 參考資料

- [Huffman Coding - Wikipedia](https://en.wikipedia.org/wiki/Huffman_coding)
- [資訊理論基礎](https://en.wikipedia.org/wiki/Information_theory)
