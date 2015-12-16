package br.edu.ifba.sispe.pocoescuro;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;

import org.primefaces.model.chart.Axis;
import org.primefaces.model.chart.AxisType;
import org.primefaces.model.chart.CartesianChartModel;
import org.primefaces.model.chart.LineChartModel;
import org.primefaces.model.chart.LineChartSeries;
import org.primefaces.model.chart.MeterGaugeChartModel;

import br.edu.ifba.sispe.pocoescuro.conector.SingleConector;

@ManagedBean(name = "monitor")
public class monitor implements Serializable{

	private LineChartModel graficoAnimal;

	public LineChartModel getGraficoAnimal() {
		return graficoAnimal;
	}

	@PostConstruct
	public void iniciar() {
		configurarMedidores();
	}

	private void configurarMedidores() {
		graficoAnimal = initGraficoAnimal();
        graficoAnimal.setTitle("Mico Leão Dourado");
        graficoAnimal.setLegendPosition("e");
        Axis yAxis = graficoAnimal.getAxis(AxisType.Y);
        yAxis.setMin(0);
        yAxis.setMax(10);
	}

	private LineChartModel initGraficoAnimal() {
		LineChartModel model = new LineChartModel();
 
        LineChartSeries series1 = new LineChartSeries();
        series1.setLabel("Series 1");
 
        series1.set(1, 2);
        series1.set(2, 1);
        series1.set(3, 3);
        series1.set(4, 6);
        series1.set(5, 8);
 
        LineChartSeries series2 = new LineChartSeries();
        series2.setLabel("Series 2");
 
        series2.set(1, 6);
        series2.set(2, 3);
        series2.set(3, 2);
        series2.set(4, 7);
        series2.set(5, 9);
 
        model.addSeries(series1);
        model.addSeries(series2);
         
        return model;
    }

	public boolean getMovimentoDetectado() {
		return (SingleConector.getInformacao().getMovimento() == 1);
	}

	public void lerSensores() {
		// acionar a temperatura do arduino
		// SingleConector.getConector().ler();
		Informacao info = SingleConector.getInformacao();

		int altitude = info.getAltitude();
		int velocidade = info.getVelocidade();

		System.out.println("Altitude " + info.getAltitude());
		System.out.println("Velocidade " + info.getVelocidade());
		System.out.println("movimento " + info.getMovimento());
		
	}
}
