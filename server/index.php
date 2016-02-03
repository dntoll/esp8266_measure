<?php


class MeasureView {
    
    private static $startID = "start";
    private static $stopID = "stop";
    private static $stateID = "stop";
    
    public function getMeasure() {
        $ids = array(self::$startID, self::$stopID, self::$stateID);
        
        foreach ($ids as $id) {
            if (isset($_REQUEST[$id]) == FALSE) {
                    echo "no $id-key supplied";
                    exit(-1);
            }
            if (is_integer($_REQUEST[$id]) == FALSE) {
                    echo "$id-key was not integer";
                    exit(-1);
            }
        }
    }
}