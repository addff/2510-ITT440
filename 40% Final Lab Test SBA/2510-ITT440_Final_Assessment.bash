#!/bin/bash

timestamp=$(TZ=Asia/Kuala_Lumpur date)
mkdir -p 2510-ITT440_Final_Assessment/
echo "2510-ITT440 Final Assessment"
echo "Final Lab Test - Skill Based Assessment"
echo "Shell Script for Answer Template"
echo "Make sure you run on UNIX or LINUX with tree installed"
echo "Good Luck - Kelassir"
echo ""
read -p "Enter Your Shortname (one word only): " nama_singkatan

while true; do
    echo "Pilih bahagian untuk dijalankan:"
    echo "1. Section 1"
    echo "2. Section 2"
    echo "3. Section 3"
    echo "4. Exit"
    read -p "Masukkan pilihan anda (1/2/3/4): " pilihan

    case $pilihan in
        1)
            # Section 1
            read -p "Enter Your Full Name (CAPITAL LETTER): " nama
            read -p "Enter Your Student ID: " nombor_pelajar
            cd 2510-ITT440_Final_Assessment/
            folder_name="${nama_singkatan}_q1"
            mkdir "$folder_name"
            cd "$folder_name"
            echo "// Name: $nama" > "2510-ITT440_${nama_singkatan}_q1.c"
            echo "// Student ID: $nombor_pelajar" >> "2510-ITT440_${nama_singkatan}_q1.c"
            echo "// Shortname: $nama_singkatan" >> "2510-ITT440_${nama_singkatan}_q1.c"
            echo "// Date: $timestamp" >> "2510-ITT440_${nama_singkatan}_q1.c"
			echo "// Q1 (FORK) 2510-ITT440 FA" >> "2510-ITT440_${nama_singkatan}_q1.c"
            echo "Maklumat telah disimpan dalam fail 2510-ITT440_${nama_singkatan}_q1.c"
            cd ..
			folder_name="${nama_singkatan}_q2"
			mkdir "$folder_name"
			cd "$folder_name"
			echo "// Name: $nama" > "2510-ITT440_${nama_singkatan}_q2_server.c"
			echo "// Student ID: $nombor_pelajar" >> "2510-ITT440_${nama_singkatan}_q2_server.c"
			echo "// Shortname: $nama_singkatan" >> "2510-ITT440_${nama_singkatan}_q2_server.c"
			echo "// Date: $timestamp" >> "2510-ITT440_${nama_singkatan}_q2_server.c"
			echo "// Q2 (C SERVER) 2510-ITT440 FA" >> "2510-ITT440_${nama_singkatan}_q2_server.c"
			echo "// Name: $nama" > "2510-ITT440_${nama_singkatan}_q2_client.c"
			echo "// Student ID: $nombor_pelajar" >> "2510-ITT440_${nama_singkatan}_q2_client.c"
			echo "// Shortname: $nama_singkatan" >> "2510-ITT440_${nama_singkatan}_q2_client.c"
			echo "// Date: $timestamp" >> "2510-ITT440_${nama_singkatan}_q2_client.c"
			echo "// Q2 (C CLIENT) 2510-ITT440 FA" >> "2510-ITT440_${nama_singkatan}_q2_client.c"
			echo "Maklumat telah disimpan dalam fail 2510-ITT440_${nama_singkatan}_q2_server.c"
			echo "Maklumat telah disimpan dalam fail 2510-ITT440_${nama_singkatan}_q2_client.c"
			cd ..
			folder_name="${nama_singkatan}_q3"
			mkdir "$folder_name"
			cd "$folder_name"
			echo "# Name: $nama" > "2510-ITT440_${nama_singkatan}_q3_server.py"
			echo "# Student ID: $nombor_pelajar" >> "2510-ITT440_${nama_singkatan}_q3_server.py"
			echo "# Shortname: $nama_singkatan" >> "2510-ITT440_${nama_singkatan}_q3_server.py"
			echo "# Date: $timestamp" >> "2510-ITT440_${nama_singkatan}_q3_server.py"
			echo "# Q3 (Py SERVER) 2510-ITT440 FA" >> "2510-ITT440_${nama_singkatan}_q3_server.py"
			echo "# Name: $nama" > "2510-ITT440_${nama_singkatan}_q3_client.py"
			echo "# Student ID: $nombor_pelajar" >> "2510-ITT440_${nama_singkatan}_q3_client.py"
			echo "# Shortname: $nama_singkatan" >> "2510-ITT440_${nama_singkatan}_q3_client.py"
			echo "# Date: $timestamp" >> "2510-ITT440_${nama_singkatan}_q3_client.py"
			echo "# Q3 (Py CLIENT) 2510-ITT440 FA" >> "2510-ITT440_${nama_singkatan}_q3_client.py"
			echo "Maklumat telah disimpan dalam fail 2510-ITT440_${nama_singkatan}_q3_server.py"
			echo "Maklumat telah disimpan dalam fail 2510-ITT440_${nama_singkatan}_q3_client.py"
			cd ..
			folder_name="${nama_singkatan}_q4"
			mkdir "$folder_name"
			cd "$folder_name"
			echo "# Name: $nama" > "2510-ITT440_${nama_singkatan}_q4.py"
			echo "# Student ID: $nombor_pelajar" >> "2510-ITT440_${nama_singkatan}_q4.py"
			echo "# Shortname: $nama_singkatan" >> "2510-ITT440_${nama_singkatan}_q4.py"
			echo "# Date: $timestamp" >> "2510-ITT440_${nama_singkatan}_q4.py"
			echo "# Q4 (PARALLEL) 2510-ITT440 FA" >> "2510-ITT440_${nama_singkatan}_q4.py"
			echo "Maklumat telah disimpan dalam fail 2510-ITT440_${nama_singkatan}_q4.py"
			cd ../..
            ;;
        2)
            # Section 2
			folder_name="${nama_singkatan}_q1" 
			cd 2510-ITT440_Final_Assessment/
			cd "$folder_name"
            gcc -o "${nama_singkatan}" "2510-ITT440_${nama_singkatan}_q1.c"
			#cat "2510-ITT440_${nama_singkatan}_q1.c"
            echo "Kompilasi selesai. Fail output: ${nama_singkatan}"
			cd ../..
            ;;
        3)
            # Section 3
			folder_name="${nama_singkatan}_q1" 
			cd 2510-ITT440_Final_Assessment/
			cd "$folder_name"
			#cp "2510-ITT440_${nama_singkatan}_q1.c" "${nama_singkatan}"
            if [ -f "${nama_singkatan}" ]; then
                ./"${nama_singkatan}"
				#cat "${nama_singkatan}"
                echo "Program ${nama_singkatan} telah dijalankan."
            else
                echo "Fail output ${nama_singkatan} tidak wujud."
            fi
			cd ../..
            ;;
        4)
            # Exit
            echo "Keluar dari skrip."
            break
            ;;
        *)
            echo "Pilihan tidak sah."
            ;;
    esac

    echo "Adakah anda ingin kembali ke menu utama atau keluar?"
    echo "1. Kembali ke menu utama"
    echo "2. Keluar"
    read -p "Masukkan pilihan anda (1/2): " pilihan_ulang

    if [ "$pilihan_ulang" -ne 1 ]; then
        echo "Keluar dari skrip."
        break
    fi
done

tree 2510-ITT440_Final_Assessment