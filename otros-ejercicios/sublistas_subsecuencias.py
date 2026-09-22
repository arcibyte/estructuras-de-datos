entrada = input("Ingresa una cadena o elementos (ej: abab): ")
sublistas = []

for i in range(len(entrada)):
    for j in range(i + 1, len(entrada) + 1):
        sub = entrada[i:j]
        if sub not in sublistas:
            sublistas.append(sub)
print(sublistas)


def generar_subsecuencias(texto):
    resultado = [""]
    
    for caracter in texto:
        nuevas_combinaciones = [sub + caracter for sub in resultado]
        resultado.extend(nuevas_combinaciones)
        
    subsecuencias_unicas = set(resultado)
    if "" in subsecuencias_unicas:
        subsecuencias_unicas.remove("")
        
    return sorted(list(subsecuencias_unicas), key=len)

print(generar_subsecuencias(entrada))