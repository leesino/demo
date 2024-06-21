package com.example.compose.sample


import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.BoxWithConstraints
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp


@Composable
fun BoxSample() {
    Box(
        contentAlignment = Alignment.Center,
        modifier = Modifier.fillMaxSize()
            .background(Color.Gray)
    ) {
        Box(Modifier.size(100.dp)
            .background(Color.Cyan)){}
    }

}

@Composable
fun BoxSample0() {
    Box {
        Box(
            Modifier
                .fillMaxSize()
                .background(Color.Cyan))
        Box(
            Modifier
                .matchParentSize()
                .padding(top = 20.dp, bottom = 20.dp)
                .background(Color.Yellow)
        )
        Box(
            Modifier
                .matchParentSize()
                .padding(40.dp)
                .background(Color.Magenta)
        )
        Box(
            Modifier
                .align(Alignment.Center)
                .size(300.dp, 300.dp)
                .background(Color.Green)
        )
        Box(
            Modifier
                .align(Alignment.TopStart)
                .size(150.dp, 150.dp)
                .background(Color.Red)
        )
        Box(
            Modifier
                .align(Alignment.BottomEnd)
                .size(150.dp, 150.dp)
                .background(Color.Blue)
        )
    }

}

@Composable
fun BoxSample1() {
    BoxWithConstraints(modifier = Modifier.size(width = 50.dp, height = 180.dp)) {
        val rectangleHeight = 100.dp
        if (maxHeight < rectangleHeight * 2) {
            Box(
                Modifier
                    .size(50.dp, rectangleHeight)
                    .background(Color.Blue))
        } else {
            Column {
                Box(
                    Modifier
                        .size(50.dp, rectangleHeight)
                        .background(Color.Green))
                Box(
                    Modifier
                        .size(50.dp, rectangleHeight)
                        .background(Color.Yellow))
            }
        }
    }
}

@Preview
@Composable
fun BoxSamplePreview() {
    BoxSample()
}
