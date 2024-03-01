# Para ler os XML tem de instalar o seguinte comando (UBUNTO)
- sudo apt-get install libpugixml-dev

# Para complilar depois usa-se (para o ficheiro exemplo.xml)
- g++ -o ler_XML ler_XML.cpp -std=c++11 -lpugixml
- ./ler_XML exemplo.xml