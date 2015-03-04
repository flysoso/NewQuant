#ifndef MATRIX_TYPE_H
#define MATRIX_TYPE_H

namespace NewQuant
{
    class MatrixType
    {
    public:
        enum Type
        {
            MatrixExpression,
            Matrix,
            SquareMatrix,
            RowVector,
            ColumnVector,
            BandMatrix,
            LowerBandMatrix,
            UpperBandMatrix,
            SymmetricBandMatrix,
            SymmetricMatrix,
            LowerTriangularMatrix,
            UpperTriangularMatrix,
            DiagonalMatrix,
            IdentityMatrix,
            ConstantMatrix,
            TridiagonalMatrix,
            PermuteMatrix
        };

    private:
        Type type;
    public:
        explicit MatrixType(const MatrixType::Type &i) : type(i) {}

        MatrixType(const MatrixType& mt) : type(mt.type) {}

        MatrixType & operator=(const MatrixType& mt)
        {
            if (&mt == this)
            {
                return *this;
            }
            type = mt.type;
            return *this;
        }

        const char * Value() const
        {
            switch (type)
            {
            case Type::MatrixExpression:
                return "MatrixExpression";
                break;
            case Type::Matrix:
                return "Matrix";
                break;
            case Type::SquareMatrix:
                return "SquareMatrix";
                break;
            case Type::BandMatrix:
                return "BandMatrix";
                break;
            case Type::LowerBandMatrix:
                return "LowerBandMatrix";
                break;
            case Type::UpperBandMatrix:
                return "UpperBandMatrix";
                break;
            case Type::SymmetricBandMatrix:
                return "SymmetricBandMatrix";
                break;
            case Type::SymmetricMatrix:
                return "SymmetricMatrix";
                break;
            case Type::LowerTriangularMatrix:
                return "LowerTriangularMatrix";
                break;
            case Type::UpperTriangularMatrix:
                return "UpperTriangularMatrix";
                break;
            case Type::DiagonalMatrix:
                return "DiagonalMatrix";
                break;
            case Type::IdentityMatrix:
                return "IdentityMatrix";
                break;
            case Type::RowVector:
                return "RowVector";
                break;
            case Type::ColumnVector:
                return "ColumnVector";
                break;
            case Type::ConstantMatrix:
                return "ConstantMatrix";
                break;
            case Type::TridiagonalMatrix:
                return "TridiagonalMatrix";
                break;
            case Type::PermuteMatrix:
                return "PermuteMatrix";
                break;
            default:
                return "UnknownType";
                break;
            }
        }

        friend bool operator == (const MatrixType &, const MatrixType &);

        friend bool operator != (const MatrixType &, const MatrixType &);
    };

    inline bool operator == (const MatrixType &a, const MatrixType &b)
    {
        return a.type == b.type;
    }

    inline bool operator != (const MatrixType &a, const MatrixType &b)
    {
        return a.type != b.type;
    }
}
#endif //MATRIX_TYPE_H

