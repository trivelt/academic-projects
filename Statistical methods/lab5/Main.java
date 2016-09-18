import java.util.Random;


public class Main {

	public static void main(String[] args) {//		
		
		double[][] matrix1 = new double[][]{{0.64, 0.32, 0.04}, {0.4, 0.5, 0.1}, {0.25, 0.5, 0.25}};
		double[][] matrix2 = new double[][]{{0.3, 0.6, 0.1}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
//		double[][] matrix3 = multiply(matrix1, matrix1);
		double[][] matrixTmp;// = multiplicar(matrix1, m/atrix1);
//		
////		showMatix(matrix2);
//		
		do {		
			matrixTmp = matrix2.clone();
			matrix2 = multiply(matrix2, matrix1);			
			
		} while(!check(matrix2, matrixTmp)); 
					
		showMatix(matrix2);
		
//		
//		double[][] probability = new double[][]{{0.64, 0.96}, {0.4, 0.9}, {0.25, 0.75}};
//		
//		int[] counter = new int[3];
//		int licznik = 100000;
//		int node = 0;
//		
//		for(int c = 0; c < licznik; ++c) {
////			for(int i = 0; i < 3; ++i) {
////				for(int j = 0; j < 3; ++j)
//				int nodeTmp = node;
//				node = getNewNodeWithProbability(probability, node);
////				System.out.println(node);
////				int nodeTmp = node;
//				counter[node]++;
////			}
//		}
//		
//		for(int i = 0; i < 3; ++i) {
//			
//				System.out.print(counter[i]/(double)licznik + " ");
//			System.out.println();
//		}
//	
		
	}
	
	public static int getNewNodeWithProbability(double[][] probability, int actualNode) {
		
		Random random = new Random();
		double randomDouble = 0;
		randomDouble = (double)random.nextInt(100)/(double)100;
//		System.out.println(randomDouble);
		
		if(randomDouble < probability[actualNode][0])
			return 0;
		else if(randomDouble >= probability[actualNode][0] && randomDouble < probability[actualNode][1])
			return 1;
		else if (randomDouble >= probability[actualNode][1] && randomDouble < 1.0)
			return 2;
		else
			return 3;
			
	}
	
	public static double[][] multiply(double[][] A, double[][] B) {
        int mA = A.length;
        int nA = A[0].length;
        int mB = B.length;
        int nB = B[0].length;
        if (nA != mB) throw new RuntimeException("Illegal matrix dimensions.");
        double[][] C = new double[mA][nB];
        for (int i = 0; i < mA; i++)
            for (int j = 0; j < nB; j++)
                for (int k = 0; k < nA; k++)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }
	
	public static void showMatix(double[][] a) {
		
		for(int i = 0; i < a[0].length; ++i) {
			for (int j = 0; j < a[0].length; ++j) {
				System.out.print(a[i][j] + " ");
			}
			System.out.println();
		}
			
	}

	public static boolean check(double[][]a, double[][]b) {
		
		int length = a[0].length;
//		boolean isOk = true;
		
		for (int i = 0; i < length; i++) { 
            for (int j = 0; j < length; j++) {
                if(Math.abs(a[i][j] - b[i][j]) > 10e-5) {
//                	System.out.println("roznica = " + Math.abs(a[i][j] - b[i][j])); 
                	return false;
                }
            }
        }
		return true;
	}
	
	

}
