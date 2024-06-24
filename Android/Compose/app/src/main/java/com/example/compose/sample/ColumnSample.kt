package com.example.compose.sample


import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.ExperimentalLayoutApi
import androidx.compose.foundation.layout.FlowColumn
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.layout.wrapContentHeight
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp


@Composable
fun ColumnSample(){
    Column(
        Modifier
            .size(40.dp, 300.dp)
            .background(Color.Gray)) {

        // The child with no weight will have the specified size.
        Box(
            Modifier
                .size(40.dp, 80.dp)
                .background(Color.Magenta))
        // Has weight, the child will occupy half of the remaining height.
        Box(
            Modifier
                .width(40.dp)
                .weight(1f)
                .background(Color.Yellow))
        // Has weight and does not fill, the child will occupy at most half of the remaining height.
        // Therefore it will occupy 80.dp (its preferred height) if the assigned height is larger.
        Box(
            Modifier
                .size(40.dp, 180.dp)
                .weight(1f, fill = false)
                .background(Color.Green))
        Box(Modifier
            .size(40.dp, 10.dp)
            .background(Color.Magenta))
    }
}

@Composable
fun ColumnSample0(){
    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = "Hello")
        Text(text = "World")
        Button(onClick = { /* Do something */ }) {
            Text(text = "Click me")
        }
    }
}

@Composable
fun ColumnSample1(){
    Column(Modifier.fillMaxWidth()) {
        Column (Modifier.fillMaxWidth(),
            horizontalAlignment = Alignment.Start){
            Text(text = "左对齐", fontSize = 24.sp,
                modifier = Modifier.background(Color.Red))
        }
        Column (Modifier.fillMaxWidth(),
            horizontalAlignment = Alignment.CenterHorizontally){
            Text(text = "水平居中齐", fontSize = 24.sp,
                modifier = Modifier.background(Color.Green))
        }
        Column (Modifier.fillMaxWidth(),
            horizontalAlignment = Alignment.End){
            Text(text = "右对齐", fontSize = 24.sp,
                modifier = Modifier.background(Color.Blue))
        }
    }
}

@Composable
fun ColumnSample2(){
    Row {
        Column(Modifier.size(20.dp,200.dp),
            verticalArrangement = Arrangement.SpaceEvenly) {
            Text(text = "1", modifier = Modifier
                .background(Color.Green)
                .size(20.dp))
            Text(text = "2",modifier = Modifier
                .background(Color.Yellow)
                .size(20.dp))
            Text(text = "3",modifier = Modifier
                .background(Color.Red)
                .size(20.dp))
        }
        Column(Modifier.size(20.dp,200.dp),
            verticalArrangement = Arrangement.SpaceBetween) {
            Text(text = "1", modifier = Modifier
                .background(Color.Green)
                .size(20.dp))
            Text(text = "2",modifier = Modifier
                .background(Color.Yellow)
                .size(20.dp))
            Text(text = "3",modifier = Modifier
                .background(Color.Red)
                .size(20.dp))
        }
        Column(Modifier.size(20.dp,200.dp),
            verticalArrangement = Arrangement.SpaceAround) {
            Text(text = "1", modifier = Modifier
                .background(Color.Green)
                .size(20.dp))
            Text(text = "2",modifier = Modifier
                .background(Color.Yellow)
                .size(20.dp))
            Text(text = "3",modifier = Modifier
                .background(Color.Red)
                .size(20.dp))
        }
        Column(Modifier.size(20.dp,200.dp),
            verticalArrangement = Arrangement.Top) {
            Text(text = "1", modifier = Modifier
                .background(Color.Green)
                .size(20.dp))
            Text(text = "2",modifier = Modifier
                .background(Color.Yellow)
                .size(20.dp))
            Text(text = "3",modifier = Modifier
                .background(Color.Red)
                .size(20.dp))
        }
        Column(Modifier.size(20.dp,200.dp),
            verticalArrangement = Arrangement.Center) {
            Text(text = "1", modifier = Modifier
                .background(Color.Green)
                .size(20.dp))
            Text(text = "2",modifier = Modifier
                .background(Color.Yellow)
                .size(20.dp))
            Text(text = "3",modifier = Modifier
                .background(Color.Red)
                .size(20.dp))
        }
        Column(Modifier.size(20.dp,200.dp),
            verticalArrangement = Arrangement.Bottom) {
            Text(text = "1", modifier = Modifier
                .background(Color.Green)
                .size(20.dp))
            Text(text = "2",modifier = Modifier
                .background(Color.Yellow)
                .size(20.dp))
            Text(text = "3",modifier = Modifier
                .background(Color.Red)
                .size(20.dp))
        }
    }
}

@OptIn(ExperimentalLayoutApi::class)
@Composable
fun FlowColumnSample(){
    Text(modifier = Modifier
        .fillMaxWidth(1f)
        .padding(20.dp)
        .wrapContentHeight(align = Alignment.Top),
        text = "FlowColumn with weights",
        fontWeight = FontWeight.Bold
    )

    FlowColumn(
        Modifier
            .padding(20.dp)
            .fillMaxWidth()
            .padding(20.dp)
            .wrapContentHeight(align = Alignment.Top)
            .height(200.dp)
            .border(BorderStroke(2.dp, Color.Gray)),
        horizontalArrangement = Arrangement.spacedBy(10.dp),
        verticalArrangement = Arrangement.spacedBy(20.dp),
        maxItemsInEachColumn = 3,
    ) {

        repeat(17) { index ->
            Box(
                Modifier
                    .align(Alignment.CenterHorizontally)
                    .width(50.dp)
                    .height(50.dp)
                    .weight(1f, true)
                    .background(color = Color.Green)
            ) {
                Text(text = index.toString(), fontSize = 18.sp, modifier = Modifier.padding(3.dp))
            }
        }
    }
}



@Preview
@Composable
fun ColumnSamplePreview() {
    ColumnSample0()
}
