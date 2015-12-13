package br.edu.ifba.sispe.pocoescuro.conector;

import br.edu.ifba.sispe.pocoescuro.IComunicacaoRF;

import com.sun.jna.Native;
import com.sun.jna.Platform;

public class FabricaConectores {
	public static IComunicacaoRF getConector(String libPath) {
		IComunicacaoRF comRF = null;

		System.out.println("libPath = " + libPath);
		if (Platform.isWindows()) {

			comRF = (IComunicacaoRF) Native.loadLibrary(libPath + "\\pocoEscuro.dll", IComunicacaoRF.class);
			
		} else if (Platform.isLinux()) {
			comRF = (IComunicacaoRF) Native.loadLibrary(libPath
					+ "\\pocoEscuro.so", IComunicacaoRF.class);
		}
		return comRF;
	}
}
