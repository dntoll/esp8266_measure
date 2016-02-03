<?php

namespace view;

class MeasureView {
    
    private static $startID = "start";
    private static $stopID = "stop";
    private static $stateID = "stop";
    
    public function getStateChange() : StateChange {
        $ids = array(self::$startID, self::$stopID, self::$stateID);
        
        foreach ($ids as $id) {
            if (isset($_REQUEST[$id]) == FALSE) {
                    throw new \Exception("no $id-key supplied");
            }
            //not needed in PHP 7.
            if (is_integer($_REQUEST[$id]) == FALSE) {
                    throw new \Exception("$id-key was not integer");
            }
        }
        
        return new \model\StateChange($_REQUEST[self::$stopID],
                           $_REQUEST[self::$startID], 
                           $_REQUEST[self::$stopID])
    }
}