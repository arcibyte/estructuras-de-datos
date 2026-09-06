def resolver_capicua(numero):
    for intento in range(100):
        texto_numero = str(numero)
        texto_reverso = texto_numero[::-1]

        numero_reverso = int(texto_reverso)

        numero = numero + numero_reverso

        resultado_texto = str(numero)
        resultado_al_reves = resultado_texto[::-1]

        if resultado_texto == resultado_al_reves:
            return numero

    return "imposible"

print("para 14 la respuesta es", resolver_capicua(14))
