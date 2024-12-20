local lspconfig = require('lspconfig')

local function get_compile_commands_dir()
  local cwd = vim.fn.getcwd()  -- Get the current working directory
  local compile_commands_file = cwd .. "/build/compile_commands.json"

  if vim.fn.filereadable(compile_commands_file) == 1 then
    return cwd .. "/build"
  end

  return nil
end

local build_dir = get_compile_commands_dir()

if build_dir then
  lspconfig.clangd.setup({
    cmd = { "clangd", "--compile-commands-dir=" .. build_dir }
  })
else
  lspconfig.clangd.setup({
    cmd = { "clangd" }  -- Fallback without compile_commands.json
  })
end

