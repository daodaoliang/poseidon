#ifndef POSEIDON_CXX_VER_HPP_
#define POSEIDON_CXX_VER_HPP_

#include <utility>
#include <memory>
#include <cstddef>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#if __cplusplus >= 201103l
#	define POSEIDON_CXX11
#endif

#if __cplusplus >= 201402l
#	define POSEIDON_CXX14
#endif

#ifdef POSEIDON_CXX11
#	define DECLTYPE(expr_)			decltype(expr_)
#	define CONSTEXPR				constexpr
#	define NOEXCEPT					noexcept
#else
#	define DECLTYPE(expr_)			__typeof__(expr_)
#	define CONSTEXPR
#	define NOEXCEPT					throw()
#endif

namespace Poseidon {

template<typename T>
typename boost::remove_cv<
	typename boost::remove_reference<T>::type
	>::type
	valueOfHelper(const T &) NOEXCEPT;

struct Nullptr_t {
#ifdef POSEIDON_CXX11
	explicit
#endif
	CONSTEXPR operator bool() const NOEXCEPT {
		return false;
	}

	template<typename T>
	CONSTEXPR operator T *() const NOEXCEPT {
		return 0;
	}
	template<typename C, typename M>
	CONSTEXPR operator C M::*() const NOEXCEPT {
		return 0;
	}
#ifdef POSEIDON_CXX11
	CONSTEXPR operator std::nullptr_t() const noexcept {
		return nullptr;
	}
#endif

	template<typename T>
	operator std::auto_ptr<T>() const NOEXCEPT {
		return std::auto_ptr<T>();
	}
#ifdef POSEIDON_CXX11
	template<typename T, typename D>
	operator std::unique_ptr<T, D>() const NOEXCEPT {
		return std::unique_ptr<T, D>();
	}
	template<typename T>
	operator std::shared_ptr<T>() const NOEXCEPT {
		return std::shared_ptr<T>();
	}
	template<typename T>
	operator std::weak_ptr<T>() const NOEXCEPT {
		return std::weak_ptr<T>();
	}
#endif

	template<typename T>
	operator boost::scoped_ptr<T>() const NOEXCEPT {
		return boost::scoped_ptr<T>();
	}
	template<typename T>
	operator boost::scoped_array<T>() const NOEXCEPT {
		return boost::scoped_array<T>();
	}
	template<typename T>
	operator boost::shared_ptr<T>() const NOEXCEPT {
		return boost::shared_ptr<T>();
	}
	template<typename T>
	operator boost::weak_ptr<T>() const NOEXCEPT {
		return boost::weak_ptr<T>();
	}

private:
	void *unused;

private:
	void operator&() const;
};

template<typename T>
typename boost::add_reference<T>::type declRef() NOEXCEPT;

#ifdef POSEIDON_CXX11
template<typename T>
using Move = typename boost::remove_reference<T>::type &&;
#else
template<typename T>
class Move {
private:
	T &m_holds;

public:
	explicit Move(T &rhs) NOEXCEPT
		: m_holds(rhs)
	{
	}
	Move(const Move &rhs) NOEXCEPT
		: m_holds(rhs.m_holds)
	{
	}

public:
	void swap(T &rhs){
		using std::swap;
		swap(m_holds, rhs);
	}
	void swap(Move &rhs){
		using std::swap;
		swap(m_holds, rhs.m_holds);
	}

public:
	operator T() const {
		T ret;
		using std::swap;
		swap(ret, m_holds);
		return ret;	// RVO
	}
};

template<typename T>
class Move<Move<T> > : public Move<T> {
private:
	typedef Move<T> Delegate;

public:
	explicit Move(T &rhs) NOEXCEPT
		: Delegate(rhs)
	{
	}
	Move(const Delegate &rhs) NOEXCEPT
		: Delegate(rhs)
	{
	}
	Move(const Move &rhs) NOEXCEPT
		: Delegate(rhs)
	{
	}

public:
	using Delegate::swap;

	void swap(Move &rhs){
		Delegate::swap(rhs);
	}

public:
	using Delegate::operator T;
};

template<typename T>
void swap(Move<T> &lhs, Move<T> &rhs){
	lhs.swap(rhs);
}
template<typename T>
void swap(Move<T> &lhs, T &rhs){
	lhs.swap(rhs);
}
template<typename T>
void swap(T &lhs, Move<T> &rhs){
	rhs.swap(lhs);
}
#endif

template<typename T>
Move<T> move(const T &rhs) NOEXCEPT {
	return Move<T>(const_cast<T &>(rhs));
}
template<typename T>
Move<T> move(T &rhs) NOEXCEPT {
	return Move<T>(rhs);
}
template<typename T>
Move<T> move(Move<T> rhs) NOEXCEPT {
	return rhs;
}

}

#ifdef POSEIDON_CXX11
#	define AUTO(id_, init_)			auto id_ = init_
#	define AUTO_REF(id_, init_)		auto &id_ = init_
#	define NULLPTR					(::Poseidon::Nullptr_t())	// (nullptr)
#	define STD_MOVE(expr_)			(::std::move(expr_))
#	define STD_FORWARD(t_, expr_)	(::std::forward<t_>(expr_))
#	define DECLREF(t_)				(::std::declval<typename ::std::remove_reference<t_>::type>())
#else
#	define AUTO(id_, init_)			DECLTYPE(::Poseidon::valueOfHelper(init_)) id_(init_)
#	define AUTO_REF(id_, init_)		DECLTYPE(init_) &id_ = (init_)
#	define NULLPTR					(::Poseidon::Nullptr_t())
#	define STD_MOVE(expr_)			(::Poseidon::move(expr_))
#	define STD_FORWARD(t_, expr_)	(expr_)
#	define DECLREF(t_)				(::Poseidon::declRef<t_>())
#endif

#endif