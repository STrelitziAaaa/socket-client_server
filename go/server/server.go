package main

import (
	// "bufio"
	"fmt"
	"net"
	"strings"
)

func handleErr(err error) {
	if err != nil {
		fmt.Println(err)
		panic(err.Error())
	}
}

func main() {
	ls, err := net.Listen("tcp", ":9999")
	handleErr(err)
	for {
		conn, err := ls.Accept()
		handleErr(err)
		go func(conn net.Conn) {
			defer conn.Close()
			for {
				//处理建立的tcp连接
				// fmt.Println("localAddr:", conn.LocalAddr().String())
				fmt.Println("remoteAddr:", conn.RemoteAddr().String())
				var buf = [1024]byte{}
				n, err := conn.Read(buf[:])
				handleErr(err)
				fmt.Println("Read:", string(buf[:n]), "len:", n)
				conn.Write([]byte("收到!"))
				if strings.ToUpper(string(buf[:n])) == "END"{
					fmt.Println("END")
					return
				}
			}
		}(conn)
		// conn.Close() 不用关闭,上面的传参不是复制
	}
}
