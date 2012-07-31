private function getSlider1Num(e:Event):void {
    var sNum:Number = xs1.passNum;
    it1.text = String(sNum);
}
        
private function getSlider2Num(e:Event):void {
    var sNum2:Number = xs2.passNum;
    it2.text = String(sNum2);
}
        
private function scaleBox(e:Event):void {
    var sNum3:Number = xs3.passNum;
    redBox.scaleX = sNum3;
    redBox.scaleY = sNum3;
}
        
private function getSlider4Num(e:Event):void {
    var sNum4:Number = xs4.passNum;
    it3.text = String(sNum4);
}
