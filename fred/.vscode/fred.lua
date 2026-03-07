---@meta

---@class FredLib
---@field version fun(): string Returns Fred's version string
fred = {}

---Returns the current Fred version
---@return string
function fred.version() end

---Wraps text in a color
---@param text string
---@param color? string Optional: "red", "green", "blue"
---@return string
function fred.color(text, color) end

---Wraps text in a style
---@param text string
---@param style? string Optional: "bold", "italic", "underline"
---@return string
function fred.style(text, style) end