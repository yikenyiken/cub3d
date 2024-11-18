#!/bin/zsh

git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42

cd ~/goinfre &&
mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew

brew install glfw