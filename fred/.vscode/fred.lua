---@meta

---@class FredLib
fred = {}

---Returns the current Fred version
---@return string
function fred.version() end

---Returns the current platform: "windows", "linux", or "mac"
---@return string
function fred.platform() end

---Exits the program cleanly
---@param code? number Optional exit code (default 0)
function fred.exit(code) end

---Wraps text in a color
---@param text string
---@param color? string Optional: "red", "green", "blue", "yellow", "cyan", "white"
---@return string
function fred.color(text, color) end

---Wraps text in a style
---@param text string
---@param style? string Optional: "bold", "italic", "underline", "dim"
---@return string
function fred.style(text, style) end

---Reads a line of user input
---@param prompt? string Optional prompt to show before input
---@return string
function fred.read(prompt) end

---Returns current unix timestamp
---@return number
function fred.time() end

---Returns formatted date string
---@param format? string Optional strftime format (default "%Y-%m-%d %H:%M:%S")
---@return string
function fred.date(format) end

---@class FredFS
fred.fs = {}

---Reads a file and returns its contents
---@param path string
---@return string|nil content
---@return string|nil error
function fred.fs.read(path) end

---Writes a string to a file
---@param path string
---@param content string
---@return boolean success
---@return string|nil error
function fred.fs.write(path, content) end

---Returns true if a file exists
---@param path string
---@return boolean
function fred.fs.exists(path) end