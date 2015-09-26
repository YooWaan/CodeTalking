
package value

import (
	"strconv"
)

type Value interface {
	GetInt() int64
	GetFloat() float64
}

type Expr interface {
	GetLeft() Value
	SetLeft(v Value)
	GetRight() Value
	SetRight(v Value)
	CalcI() Value
	CalcF() Value
}

// Integer
type VarInt struct {
	i int64
}

func (v VarInt) GetInt() int64 {
	return v.i
}

func (v VarInt) GetFloat() float64 {
	return float64(v.i)
}

func (v *VarInt) Set(num int64) {
	v.i = num
}

func (v VarInt) String() string {
	return strconv.FormatInt(v.i, 10)
}

// Float
type VarFloat struct {
	f float64
}

func (v VarFloat) GetInt() int64 {
	return int64(v.f)
}

func (v VarFloat) GetFloat() float64 {
	return v.f
}

func (v *VarFloat) Set(num float64) {
	v.f = num
}

func (v VarFloat) String() string {
	return strconv.FormatFloat(v.f, 'E', -1, 64)
}

// ValuePair
type ValuePair struct {
	Left Value
	Right Value
}

// Add
type Add struct {
	ValuePair
}

func (e Add) GetLeft() Value {
	return e.Left
}

func (e *Add) SetLeft(v Value) {
	e.Left = v
}

func (e Add) GetRight() Value {
	return e.Right
}

func (e *Add) SetRight(v Value) {
	e.Left = v
}

func (e Add) GetInt() int64 {
	return e.Left.GetInt() + e.Right.GetInt()
}

func (e Add) GetFloat() float64 {
	return e.Left.GetFloat() + e.Right.GetFloat()
}

func (e Add) CalcI() Value {
	return VarInt{e.GetInt()}
}

func (e Add) CalcF() Value {
	return VarFloat{e.GetFloat()}
}


// multipy
type Mul struct {
	ValuePair
}

func (e Mul) GetLeft() Value {
	return e.Left
}

func (e *Mul) SetLeft(v Value) {
	(*e).Left = v
}

func (e Mul) GetRight() Value {
	return e.Right
}

func (e *Mul) SetRight(v Value) {
	e.Left = v
}

func (e Mul) GetInt() int64 {
	return e.Left.GetInt() * e.Right.GetInt()
}

func (e Mul) CalcI() Value {
	return VarInt{e.GetInt()}
}

func (e Mul) GetFloat() float64 {
	return e.Left.GetFloat() * e.Right.GetFloat()
}

func (e Mul) CalcF() Value {
	return VarFloat{e.GetFloat()}
}

// initializer

func NewInt(i int64) *VarInt {
	return &VarInt{i:i}
}

func NewFloat(f float64) *VarFloat {
	return &VarFloat{f:f}
}

func NewPair(left Value, right Value) *ValuePair {
	return &ValuePair{Left:left, Right:right}
}

func NewAdd(left Value, right Value) *Add {
	return &Add{ValuePair{Left:left, Right:right}}
}

func NewMul(left Value, right Value) *Mul {
	return &Mul{ValuePair{Left:left, Right:right}}
}

