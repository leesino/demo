package com.example.compose.sample


import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.aspectRatio
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Person
import androidx.compose.material3.Icon
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.BlurredEdgeTreatment
import androidx.compose.ui.draw.blur
import androidx.compose.ui.draw.clip
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.graphics.BlendMode
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.ColorFilter
import androidx.compose.ui.graphics.ColorMatrix
import androidx.compose.ui.graphics.ImageBitmap
import androidx.compose.ui.graphics.Shape
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.imageResource
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import coil.compose.AsyncImage
import com.example.compose.R


@Composable
fun IconSample() {
    Column {
        Icon(imageVector = Icons.Default.Person,
            contentDescription = null,
            modifier = Modifier.size(80.dp),
            tint = Color.Red)
        Icon(
            painter = painterResource(
                id = R.drawable.ic_launcher_foreground),
            contentDescription = null,
            tint = Color.Green
        )
    }
}

@Composable
fun ImageSample(){
    Column {
        Image(painter = painterResource(id = R.drawable.android),
            contentDescription = null,
            modifier = Modifier
                .size(90.dp)
                .background(Color.Gray))
        Image(painter = painterResource(id = R.drawable.android),
            contentDescription = null,
            contentScale = ContentScale.None,
            modifier = Modifier
                .size(90.dp)
                .background(Color.Red))
        Image(painter = painterResource(id = R.drawable.android),
            contentDescription = null,
            contentScale = ContentScale.Inside,
            modifier = Modifier
                .size(90.dp)
                .background(Color.Green))
        Image(painter = painterResource(id = R.drawable.android),
            contentDescription = null,
            contentScale = ContentScale.Fit,
            modifier = Modifier
                .size(90.dp)
                .background(Color.Yellow))
        Image(painter = painterResource(id = R.drawable.android),
            contentDescription = null,
            contentScale = ContentScale.Crop,
            modifier = Modifier
                .size(90.dp)
                .background(Color.Blue))
        Image(painter = painterResource(id = R.drawable.android),
            contentDescription = null,
            contentScale = ContentScale.FillBounds,
            modifier = Modifier
                .size(90.dp)
                .background(Color.Cyan))

        Image(painter = painterResource(id = R.drawable.android),
            contentDescription = null,
            contentScale = ContentScale.FillWidth,
            modifier = Modifier
                .size(90.dp)
                .background(Color.Magenta))
        Image(painter = painterResource(id = R.drawable.android),
            contentDescription = null,
            contentScale = ContentScale.FillHeight,
            modifier = Modifier
                .size(90.dp)
                .background(Color.Yellow))
    }
}

@Composable
fun ImageSample1(){
    Column {
        Image(painter = painterResource(id = R.drawable.dog),
            contentDescription = "圆形图片",
            contentScale = ContentScale.Crop,
            modifier = Modifier
                .size(200.dp)
                .clip(CircleShape))
        Image(painter = painterResource(id = R.drawable.dog),
            contentDescription = "圆角图片",
            contentScale = ContentScale.Crop,
            modifier = Modifier
                .size(200.dp)
                .clip(RoundedCornerShape(16.dp)))
    }
}

@Composable
fun ImageSample2(){
    val borderWidth = 6.dp
    Image(
        painter = painterResource(id = R.drawable.dog),
        contentDescription = "裁剪+边框",
        contentScale = ContentScale.Crop,
        modifier = Modifier
            .size(150.dp)
            .border(
                BorderStroke(borderWidth, Color.Red),
                CircleShape
            )
            .padding(borderWidth)
            .clip(CircleShape)
    )
}

@Composable
fun ImageSample3(){
    val rainbowColorsBrush = remember {
        Brush.sweepGradient(
            listOf(Color.Green,Color.Blue,Color.Red,Color.Cyan
            )
        )
    }
    Image(painter = painterResource(id = R.drawable.dog),
        contentDescription = "渐变边框",
        contentScale = ContentScale.Crop,
        modifier = Modifier.size(150.dp)
            .border(BorderStroke(6.dp, rainbowColorsBrush),
                CircleShape)
            .padding(6.dp)
            .clip(CircleShape)
    )
}

@Composable
fun ImageSample4(){
    Image(
        painter = painterResource(id = R.drawable.dog),
        contentDescription = "黑白处理",

        colorFilter = ColorFilter.colorMatrix(
            ColorMatrix().apply { setToSaturation(0f) })
    )
}

@Composable
fun ImageSample5(){
    Image(
        painter = painterResource(id = R.drawable.dog),
        contentDescription = "模糊处理，Android12及以上才生效",
        contentScale = ContentScale.Crop,
        modifier = Modifier
            .size(150.dp)
            .blur(
                radiusX = 10.dp,
                radiusY = 10.dp,
                edgeTreatment = BlurredEdgeTreatment(RoundedCornerShape(8.dp))
            )
    )
}


@Preview
@Composable
fun IconSamplePreview() {
    ImageSample5()
}
