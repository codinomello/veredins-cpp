package main

import (
	"fmt"
	"net"
)

func main() {
	// resolve endereço UDP
	addr, err := net.ResolveUDPAddr("udp", ":12345")
	if err != nil {
		panic(err)
	}

	// escuta na porta
	conn, err := net.ListenUDP("udp", addr)
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	fmt.Println("📠 servidor echo UDP rodando na porta 12345")

	buf := make([]byte, 1024) // buffer pra mensagens
	for {
		// lê mensagem do cliente
		n, remoteAddr, err := conn.ReadFromUDP(buf)
		if err != nil {
			continue
		}

		// imprime o que recebeu
		fmt.Printf("✅ recebido: %s de %s\n", string(buf[:n]), remoteAddr)

		// devolve a mesma mensagem (echo)
		_, err = conn.WriteToUDP(buf[:n], remoteAddr)
		if err != nil {
			fmt.Println("❌ erro ao enviar:", err)
		}
	}
}
