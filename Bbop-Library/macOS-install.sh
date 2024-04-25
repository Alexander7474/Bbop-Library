#!/bin/bash


#Méthode à suivre pour l'installation :


        #$ cd ~/Desktop/Fac/code/Bbop-Library
        #$ chmod +x macOS-install.sh
        #$ ./macOS-install.sh



# Reset
Color_Off='\033[0m'       # Text Reset

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

echo -e "${Purple}Welcome to"
cat << "EOF"
   ___    _                _ __              _                      _                _       _                    
  | _ )  | |__     ___    | '_ \    o O O   (_)    _ _      ___    | |_    __ _     | |     | |     ___      _ _  
  | _ \  | '_ \   / _ \   | .__/   o        | |   | ' \    (_-<    |  _|  / _` |    | |     | |    / -_)    | '_| 
  |___/  |_.__/   \___/   |_|__   TS__[O]  _|_|_  |_||_|   /__/_   _\__|  \__,_|   _|_|_   _|_|_   \___|   _|_|_  
_|"""""|_|"""""|_|"""""|_|"""""| {======|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'
EOF

echo_error() {
  echo -e "${Red}ERROR: $1" >&2
  exit -1
}

animate_loading() {
    local text="$1"
    local delay=0.1
    while true; do
        printf "\r$text /"
        sleep $delay
        printf "\r$text -"
        sleep $delay
        printf "\r$text \\"
        sleep $delay
        printf "\r$text |"
        sleep $delay
    done
}

install_package() {
  #creation du process pour animer le texte
  animate_loading "Installing $package " &
  local animation_pid=$!

  #on install le package avec le package manager
  if [[ $package_manager == "brew" ]]
  then
    brew install $1 &> /dev/null
  fi

  #on kill l'animation
  kill $animation_pid &> /dev/null
  echo ""

  #Check si le package s'est bien installé
  if [[ $? -ne 0 ]]
  then
    echo_error "Installation failed $1"
  else
    echo -e "${Green}$1 install with succes !"
  fi
}

detect_package() {
  if [[ $package_manager == "brew" ]]
  then
    result=$(brew list | grep $1)
  fi
  if [[ ! -z "$result" ]]
  then
    return 0
  else
    return 1
  fi
}

#Vérification des paramètres
if [[ "$#" -ne 0 ]]
then
  echo_error "This script oes not take parameters"
fi

#check si root
if [ `id -u` -eq 0 ]
then
  echo_error "This script should not be run as root on macOS!"
fi

#installation des libs nécessaires
package_manager="not_found"

#on determine le package manager
if command -v brew &> /dev/null
then
  package_manager="brew"
fi

if [[ $package_manager == "not_found" ]]
then
  echo_error "package manager not found !"
else
  echo -e "${Yellow}package manager found:${Color_Off} $package_manager"
fi

#list des package a installer
package_list=("glew" "xorg-server" "freetype" "wayland" "xkbcommon" "wayland-protocols" "stb")

echo -e "${Yellow}Installing necessary packages"
for package in "${package_list[@]}"
do
  #on cherche le package avec le package manager detecte
  echo -e "${Yellow}Installing: ${Color_Off}$package"

  #on install le package si il ne l'est pas
  if detect_package $package
  then
    echo -e "${Green}$package is already installed !"
  else
    install_package $package
  fi
done

echo -e "${Green}Package install done !"

# Installation de GLFW
echo -e "${Yellow}Installing GLFW${Color_Off}"
if brew list | grep -q "glfw"; then
    echo -e "${Green}GLFW is already installed !"
else
    brew install glfw
    echo -e "${Green}GLFW install done !"
fi

# Installation de GLM
echo -e "${Yellow}Installing GLM${Color_Off}"
if brew list | grep -q "glm"; then
    echo -e "${Green}GLM is already installed !"
else
    brew install glm
    echo -e "${Green}GLM install done !"
fi

# Installation de BBOP
echo -e "${Yellow}Installing BBOP${Color_Off}"
if [ -d "/usr/local/include/BBOP" ]; then
    echo -e "${Green}BBOP is already installed !"
else
    echo -e "${Yellow}BBOP not found in homebrew, installing from source${Color_Off}"
    git clone https://github.com/Alexander7474/Bbop-Library.git
    cd Bbop-Library
    make
    sudo make install
    cd ..
    rm -r Bbop-Library
    echo -e "${Green}BBOP install done !"
fi

echo -e "${Purple}Install finished"
cat << "EOF"
   ___       _      _                    
  /   \   __| |    (_)     ___     ___   
  | - |  / _` |    | |    / _ \   (_-<   
  |_|_|  \__,_|   _|_|_   \___/   /__/_  
_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'
EOF
