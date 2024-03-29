#!/bin/bash

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
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'                                          
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

install_packet() {
  #creation du process pour animer le texte
  animate_loading "Installing $packet " &
  local animation_pid=$!

  #on install le packet avec le packet manager
  if [[ $packet_manager == "dpkg" ]]
  then
    sudo apt install -y $1 &> /dev/null
  elif [[ $packet_manager == "rpm" ]]
  then
    sudo dnf install -y $1
  elif [[ $packet_manager == "pacman" ]]
  then
    sudo pacman -S --noconfirm $1
  fi

  #on kill l'animation
  kill $animation_pid &> /dev/null
  echo ""

  #Check si le packet c'st bien installé
  if [[ $? -ne 0 ]]
  then
    echo_error "Problème lors de l'installation de $1"
  else
    echo -e "${Green}$1 install with succes !"
  fi
}

detect_packet() {
  if [[ $packet_manager == "dpkg" ]]
  then
    result=$(dpkg -l |grep $1)
  elif [[ $packet_manager == "pacman" ]]
  then
    result=$(pacman -Q $1)
  elif [[ $packet_manager == "rpm" ]]
  then
    result=$(rpm -q $1)
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
  echo_error "Ce script ne prend pas de paramètre !"
fi

#installation des libs nécessaires
packet_manager="not_found"

#on determine le packet manager
if command -v dpkg &> /dev/null
then 
  packet_manager="dpkg"
elif command -v rpm &> /dev/null
then 
  packet_manager="rpm"
elif command -v pacman &> /dev/null
then 
  packet_manager="pacman"
fi

if [[ $packet_manager == "not_found" ]]
then
  echo_error "Packet manager not found !"
else
  echo -e "${Yellow}Packet manager found:${Color_Off} $packet_manager"
fi

#list des packet a installer
packet_list=("libglew-dev" "xorg-dev" "libfreetype6-dev" "libwayland-dev" "libxkbcommon-dev" "wayland-protocols" "libstb-dev" "extra-cmake-modules")

echo -e "${Yellow}Installing necessary packets"
for packet in "${packet_list[@]}"
do 
  #on cherche le packet avec le packet manager detecte
  echo -e "${Yellow}Installing: ${Color_Off}$packet"
  
  #on install le packet si il ne l'est pas
  if detect_packet $packet
  then
    echo -e "${Green}$packet is already installed !"
  else
    install_packet $packet
  fi
done

echo -e "${Green}Packet install done !"
