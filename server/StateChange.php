<?php

namespace model;

class StateChange {
    private $start;
    private $stop;
    private $state;
    
    public function __construct(int $start, int $end, bool $state) {
        $this->start = $start;
        $this->stop = $stop;
        $this->state = $state;
    }
    
    
}