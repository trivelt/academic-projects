class VectorSum extends VectorOperationsAbstractClass {

	public void normalize( double[] v ){
	double max=v[0];
	for(int i=0;i<v.length;i++){ // wyszukiwanie najwiekszego elementu w wektorze
		if(v[i]>max) max=v[i];
		}
	for(int i=0;i<v.length;i++){ // petla normalizujaca
		v[i]=v[i]/max;
		}
	}

	public void show( double[] v ){
	for(int i=0;i<v.length;i++){
		System.out.println("v["+i+"]="+v[i]);
		}
	}
	
	public void calc( double[] a, double[] b, double[] c ){
	for(int i=0;i<a.length;i++){
		c[i]=a[i]+b[i];
		}
	}
}


class VectorDif extends VectorOperationsAbstractClass {

	public void normalize( double[] v ){
	VectorSum tmp = new VectorSum();
	tmp.normalize(v);
	}

	public void show( double[] v ){
	VectorSum tmp = new VectorSum();
	tmp.show(v);	
	}
	
	public void calc( double[] a, double[] b, double[] c ){
	for(int i=0;i<a.length;i++){
		c[i]=a[i]-b[i];
		}
	}
}

class VectorMult extends VectorOperationsAbstractClass {

	public void normalize( double[] v ){
	VectorSum tmp = new VectorSum();
	tmp.normalize(v);
	}

	public void show( double[] v ){
	VectorSum tmp = new VectorSum();
	tmp.show(v);	
	}
	
	public void calc( double[] a, double[] b, double[] c ){
	for(int i=0;i<a.length;i++){
		c[i]=a[i]*b[i];
		}
	}
}


