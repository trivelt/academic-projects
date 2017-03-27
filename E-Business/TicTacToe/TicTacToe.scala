import scala.io.StdIn.readInt

object TicTacToe {

    var endOfGame: Boolean = false
    var inputRow: Int = -1
    var inputCol: Int = -1
    var turn: String = "x"
    
    val size: Int = 3 // minimum: 3
    var fields = Array.ofDim[String](size+1, size+1)
    
    def changeTurn() {
        turn = turn match {
            case "x" => "o"
            case "o" => "x"
        }
    }
    
    def field(row: Int, col: Int): String = {
        val character: String = fields(row)(col) 
        val num = character match {
            case null => "   "
            case "x" => " x "
            case "o" => " o "
        }
        return num;    
    }

    def showBoard() {
        for (a <- 0 to 4*size) {
           print("=")
                
        }; println
        
        for (i <- 0 to size-1) {
            for (j <- 0 to size) {
                print("|" + field(i, j))  
            }; println
            
            for (j <- 0 to 4*size) {
                print("=")
                
            }; println      
        }         
    }
    
    def getInput() {
        inputRow = -1
        inputCol = -1
        
        println("'"+turn+"', it's your turn")
    
        while(inputRow == -1 || inputCol == -1) {
            try {
                print("Row: ")
                val row = readInt()
                print("Column: ")
                val col = readInt()        
                
                if(row >= 0 && row < size && col >= 0 && col < size) {
                    if(fields(row)(col) != null) {
                        println("Wrong input: selected field is not available. Try again")
                    } else {
                        inputRow = row
                        inputCol = col
                        fields(row)(col) = turn
                        changeTurn                        
                    }
                } else { println("Wrong input: number not in range. Try again") }
                
            } catch {
                case e: Exception => println("Wrong input. Try again.")
            }
        }
    }
    
    
    def checkEndConditions() {
    
        // rzedy
        var previous: String = fields(0)(0)    
        for (row <- 0 to size-1) {
            var success: Boolean = true
            for (col <- 1 to size-1) {
                if(fields(row)(col) == null || fields(row)(col) != fields(row)(col-1)) {
                    success = false
                }
            }
            if(success == true) {
                endOfGame = true
            }
        }
        
        
        // kolumny
        previous = fields(0)(0)    
        for (col <- 0 to size-1) {
            var success: Boolean = true
            for (row <- 1 to size-1) {
                if(fields(row)(col) == null || fields(row)(col) != fields(row-1)(col)) {
                    success = false
                }
            }
            if(success == true) {
                endOfGame = true
            }
        }       
        
        
        // przekatna
        var success: Boolean = true
        for(i <- 1 to size-1) {
           if(fields(i)(i) == null || fields(i)(i) != fields(i-1)(i-1)) {
            success = false
           }
        }
        if(success == true) {
            endOfGame = true
        }
        
        
        // przekatna
        success = true
        var col: Int = size-2
        for(row <- 1 to size-1){
            if(fields(row)(col) == null || fields(row)(col) != fields(row-1)(col+1)) {
                success = false
            }
            col = col-1
        }
        if(success == true) {
            endOfGame = true
        }
                
    }

    def main(args: Array[String]) {
        while(!endOfGame) {
            showBoard
            getInput
            checkEndConditions
        }
        
        showBoard
        changeTurn
        println("End game. Winner is: " + turn)
    }

}
