// swift-tools-version:5.9

import PackageDescription

let package = Package(
    name: "mlx",
    platforms: [
        .macOS(.v14)
    ],
    products: [
        .library(name: "MLX", targets: ["MLX"]),
        .library(name: "MLXNN", targets: ["MLXNN"]),
        .library(name: "MLXOptimizers", targets: ["MLXOptimizers"]),
        .library(name: "MLXData", targets: ["MLXData"]),
        .library(name: "MLXLMCommon", targets: ["MLXLMCommon"]),
    ],
    dependencies: [],
    targets: [
        .target(name: "MLX"),
        .target(name: "MLXNN", dependencies: ["MLX"]),
        .target(name: "MLXOptimizers", dependencies: ["MLX"]),
        .target(name: "MLXData", dependencies: ["MLX"]),
        .target(name: "MLXLMCommon", dependencies: ["MLX", "MLXNN", "MLXOptimizers"]),
    ]
)

